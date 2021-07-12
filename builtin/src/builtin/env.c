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

int	m_env(t_parsed *parsed, t_dummy *out)
{
	int	ofd;

	if (out->tail->left->db == -1)
		ofd = 1;
	else if (out->tail->left->db)
		ofd = open(out->tail->left->val, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		ofd = open(out->tail->left->val, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (!search_list(g_env_list, "PATH"))
		return (TRUE);
	if (parsed->cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (parsed->cmd[2][0] != '\0')
	{
		if (!search_list(g_env_list, &parsed->cmd[2][0]))
			print_error(parsed, "?=127");
		else
			write(ofd, parsed->cmd[2], m_strlen(parsed->cmd[2]));
	}
	else
		print_list(ofd, g_env_list);
	if (ofd != 1)
		close(ofd);
	return (TRUE);
}
