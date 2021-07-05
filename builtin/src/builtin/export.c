/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:52 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:53 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int m_export(t_parsed parsed, t_dummy *std_out)
{
	int out_fds;

	if (std_out->tail->left->db == -1)
		out_fds = 1;
	else if (std_out->tail->left->db)
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_APPEND  | O_CREAT, 0777);
	else
		out_fds = open(std_out->tail->left->val, O_WRONLY | O_TRUNC | O_CREAT, 0777);

	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (parsed.cmd[2][0] >= '0' && parsed.cmd[2][0] <= '9')
		print_error(parsed, "?=1");
	else if (parsed.cmd[2][0] != '\0')
		add_list_sort(&env_list, parsed.cmd[2]);
		// insert_tree(parsed.cmd[2]);
	else
		print_list(&env_list);
	if (out_fds != 1)
		close(out_fds);
	return (TRUE);
}
