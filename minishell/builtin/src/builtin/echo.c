/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:34 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:35 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	nnnn(char *line, int idx, int flag, int ret)
{
	if (line[idx] != '-')
		return (0);
	while (line[idx])
	{
		if (line[idx] == '-')
		{
			++idx;
			if (!line[idx])
				break ;
			while (line[idx] == 'n')
			{
				++idx;
				flag = 1;
			}
		}
		if (flag && (line[idx] == 32 || !line[idx]))
			ret = idx;
		else
			return (ret);
		++idx;
		flag = 0;
	}
	return (ret);
}

int	m_echo(t_parsed *parsed, t_dummy *std_out)
{
	int	ofd;

	if (std_out->tail->left->db > 2)
		ofd = std_out->tail->left->db;
	else if (std_out->tail->left->db == 1)
		ofd = open(std_out->tail->left->val,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	else if (std_out->tail->left->db == 0)
		ofd = open(std_out->tail->left->val,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		ofd = 1;
	if (!m_strncmp(parsed->cmd[1], "-n", 2))
		write(ofd, parsed->cmd[2], m_strlen(parsed->cmd[2]));
	else
	{
		write(ofd, parsed->cmd[2], m_strlen(parsed->cmd[2]));
		write(ofd, "\n", 1);
	}
	if (ofd != 1)
		close(ofd);
	return (TRUE);
}
