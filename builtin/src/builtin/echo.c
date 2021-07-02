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

int		nnnn(char *line, int idx, int flag, int ret)
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

int		m_echo(t_parsed parsed, t_dummy *std_out)
{
	int out_fds;

	if (std_out->tail->left->db == -1)
		out_fds = 1;
	else if (std_out->tail->left->db)
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_APPEND, 0777);
	else
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_TRUNC, 0777);

	if (!m_strncmp(parsed.cmd[1], "-n", 2))
		write(out_fds, parsed.cmd[2], m_strlen(parsed.cmd[2]));
	else
	{
		write(out_fds, parsed.cmd[2], m_strlen(parsed.cmd[2]));
		write(out_fds, "\n", 1);
	}
	if (out_fds != 1)
		close(out_fds);
	return (TRUE);
}
