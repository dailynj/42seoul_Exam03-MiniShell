/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:38 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:39 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int m_env(t_parsed parsed, t_dummy *std_out)
{
	int out_fds;

	if (std_out->tail->left->db == -1)
		out_fds = 1;
	else if (std_out->tail->left->db)
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_APPEND, 0777);
	else
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_TRUNC, 0777);

	if (m_find_env("PATH") == NULL)
		return (OK);
	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (parsed.cmd[2][0] != '\0')
	{
		if (!m_find_env(&parsed.cmd[2][0]))
			print_error(parsed, "?=127");
		else
			write(g_fds, parsed.cmd[2], m_strlen(parsed.cmd[2]));
			// printf("env : %s\n", m_find_env(&parsed.cmd[2][0]));
	}
	else
		inorder_print(tree(), environ, out_fds);
	return (OK); // 수정
}
