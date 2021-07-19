/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirection2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:00 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:01 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	nl_to_null(char ch)
{
	if (ch == '\n' || ch == 4)
		return (0);
	return (ch);
}

int	get_read_buf(char *read_buf, int *i, char *val)
{
	char	ch;

	while (read(0, &ch, 1) > 0)
	{
		if (ch == 3)
		{
			write(1, "\n", 1);
			return (FALSE);
		}
		else if (ch == 4 && *i == -1)
			return (m_strlcpy(read_buf, val, m_strlen(val) + 1));
		else if (ch == 127 && *i != -1)
		{
			read_buf[(*i)--] = 0;
			write(1, "\b \b", 3);
		}
		else if (ch != 127)
		{
			write(1, &ch, 1);
			read_buf[++(*i)] = nl_to_null(ch);
			if (ch == '\n')
				break ;
		}
	}
	return (TRUE);
}

int	redi_stdin_db(t_term *term, t_list *tmp, int fd)
{
	char	*read_buf;
	int		i;

	fd = open("stdout", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	set_input_mode(term);
	read_buf = m_calloc(BUFFER_SIZE, 0);
	while (1)
	{
		i = -1;
		write(1, " > ", 3);
		if (!get_read_buf(read_buf, &i, tmp->val))
		{
			free(read_buf);
			errno = 1;
			return (reset_input_mode(term));
		}
		if (!m_strncmp(tmp->val, read_buf, m_strlen(tmp->val) + 1))
			break ;
		write(fd, read_buf, m_strlen(read_buf));
		write(fd, "\n", 1);
	}
	free(read_buf);
	close(fd);
	return (!reset_input_mode(term));
}

int	redi_stdin(t_list *node)
{
	t_list	*tmp;
	int		fd;
	t_term	term;

	tmp = node;
	fd = 0;
	init_term(&term);
	while (tmp->right)
	{
		if (tmp->db == 0)
		{
			fd = open(tmp->val, O_WRONLY, 0777);
			if (fd == -1)
				return (ret_mesg(tmp->val, "No such file or directory", -1));
			close (fd);
		}
		else if (tmp->db == 1)
		{
			if (!redi_stdin_db(&term, tmp, fd))
				return (-1);
		}
		tmp = tmp->right;
	}
	return (fd);
}

int	redi_stdout(t_list *node)
{
	t_list	*tmp;
	int		fd;

	tmp = node;
	fd = 1;
	while (tmp->right)
	{
		fd = open(tmp->val, O_WRONLY | (O_APPEND & (tmp->db << 3))
				| O_CREAT, 0777);
		tmp = tmp->right;
		close(fd);
	}
	return (fd);
}
