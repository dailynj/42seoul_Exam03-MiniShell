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

// return -1 이면 에러처리(바로 다음 command로 넘어가야함)
void	redi_stdin_db(t_list *tmp, int fd)
{
	char	read_buf[BUFFER_SIZE];

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
			// ctrl + c , ctrl + d,  \n
			write(fd, &read_buf, m_strlen(read_buf));
			write(fd, "\n", 1);
		}
	}
	close(fd);
}

int	redi_stdin(t_list *node)
{
	t_list	*tmp;
	int		fd;

	tmp = node;
	fd = 0;
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
			redi_stdin_db(tmp, fd);
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
