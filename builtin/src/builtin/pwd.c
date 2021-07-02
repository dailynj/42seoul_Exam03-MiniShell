/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:58 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:59 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int m_pwd(t_parsed parsed, t_dummy *std_out)
{
	char cwd[PATH_MAX];
	int out_fds;

	if (std_out->tail->left->db == -1)
		out_fds = 1;
	else if (std_out->tail->left->db)
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_APPEND, 0777);
	else
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_TRUNC, 0777);

	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(out_fds, cwd, m_strlen(cwd));
		write(out_fds, "\n", 1);
	}
	else
		perror("getcwd() error\n");
	return (TRUE);
}
