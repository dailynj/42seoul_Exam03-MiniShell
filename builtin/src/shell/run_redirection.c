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
		if (line[i] != ' ' && line[i] != '<' && line[i] != '>')
		{
			while (line[i] != ' ' && line[i] != '<' && line[i] != '>')
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

int	core_cmd2(char **line)
{
	if (*(*line + 1) == '<' || *(*line + 1) == '>')
		++(*line);
	++(*line);
	while (**line == ' ')
		++(*line);
	while (**line != ' ' && **line != '\0')
		++(*line);
	while (**line == ' ' && **line != '\0')
		++(*line);
	if (**line == '\0')
		return (1);
	if (**line == '<' || **line == '>')
		return (2);
	while (**line != ' ' && **line != '\0')
		++(*line);
	return (0);
}

char	*core_cmd(char *line)
{
	char	*temp;
	int		tdx;
	int		ret;

	tdx = -1;
	temp = malloc(BUFFER_SIZE);
	m_memset(temp, 0, BUFFER_SIZE);
	if (!temp)
		return (NULL);
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			ret = core_cmd2(&line);
			if (ret == 1)
				break ;
			else if (ret == 2)
				continue ;
		}
		else
			temp[++tdx] = *line;
		++line;
	}
	temp[++tdx] = 0;
	return (temp);
}

char	*join_parsed(t_parsed *parsed)
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
		while (parsed->cmd[cnt][++idx])
		{
			ret[++rdx] = parsed->cmd[cnt][idx];
		}
		ret[++rdx] = ' ';
	}
	ret[++rdx] = 0;
	return (ret);
}
