/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:00 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:01 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*first_word(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = malloc(BUFFER_SIZE);
	if (!line || !tmp)
		return (NULL);
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			while (line[i] != ' ')
			{
				tmp[++j] = line[i];
				++i;
			}
			return (tmp);
		}
	}
	tmp[i] = 0;
	return (tmp);
}

void	fill_list(char *line, char ch, t_dummy *std)
{
	char	*tmp;

	while (*line)
	{
		if (*line == ch)
		{
			if (*(line + 1) == ch)
			{
				tmp = first_word(++line);
				add_list(std->tail, tmp, 1);
			}
			else
			{
				tmp = first_word(line);
				add_list(std->tail, tmp, 0);
			}
			free(tmp);
		}
		++line;
	}
}

int		redi_stdin(t_list *node)
{
	t_list	*tmp;
	char	read_buf[BUFFER_SIZE];
	int		fd;

	tmp = node;
	fd = 0;
	while (tmp->right)
	{
		if (tmp->db == 0)
		{
			fd = open(tmp->val, O_WRONLY, 0777);
			if (fd == -1)
				return (return_message(tmp->val, "No such file or directory", -1));
			close (fd);
		}
		else if (tmp->db == 1)
		{
			fd = open("a.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
			while (1)
			{
				m_memset(&read_buf, 0, BUFFER_SIZE);
				write(1, " > ", 3);
				read(0, &read_buf, BUFFER_SIZE);
				read_buf[m_strlen(read_buf) - 1] = 0;
				if (!m_strncmp(tmp->val, read_buf, m_strlen(tmp->val) + 1))
					break ;
				else
				{
					write(fd, &read_buf, m_strlen(read_buf));
					write(fd, "\n", 1);
				}
			}
			close(fd);
		}
		tmp = tmp->right;
	}
	return (fd);
}

int		redi_stdout(t_list *node)
{
	t_list	*tmp;
	int		fd;

	tmp = node;
	fd = 1;
	while (tmp->right)
	{
		fd = open(tmp->val, O_WRONLY | (O_APPEND & (tmp->db << 3)) | O_CREAT, 0777);
		tmp = tmp->right;
		close(fd);
	}
	return (fd);
}

char	*core_cmd(char *line)
{
	char *temp;
	int tdx;

	tdx = -1;
	temp = malloc(BUFFER_SIZE);
	m_memset(temp, 0, BUFFER_SIZE);
	if (!temp)
		return (NULL);
	printf("temp : %s\n", temp);
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			if (*(line + 1) == '<' || *(line + 1) == '>')
				++line;
			++line;
			while (*line == ' ')
				++line;
			while (*line != ' ' && *line != '\0')
				++line;
			while (*line == ' ' && *line != '\0')
				++line;
			if (*line == '\0')
				break;
			if (*line == '<' || *line == '>')
				continue ;
			else
			{
				while (*line != ' ')
				{
					temp[++tdx] = *line;
					++line;
				}
				temp[++tdx] = ' ';
			}
			--line;
		}
		else
			temp[++tdx] = *line;
		++line;
	}
	temp[++tdx] = 0;
	printf("temp : %s\n", temp);
	return (temp);
}

char	*join_parsed(t_parsed parsed)
{
	char	*ret;
	int		cnt;
	int		idx;
	int		rdx;

	cnt = -1;
	rdx = -1;
	ret = malloc(BUFFER_SIZE);
	while (++cnt < 3)
	{
		idx = -1;
		while (parsed.cmd[cnt][++idx])
		{
			ret[++rdx] = parsed.cmd[cnt][idx];
		}
		ret[++rdx] = ' ';
	}
	ret[++rdx] = 0;
	return (ret);
}
