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

int	m_pwd(t_parsed *parsed, t_dummy *out)
{
	char	cwd[PATH_MAX];
	int		ofd;

	if (out->tail->left->db == -1)
		ofd = 1;
	else if (out->tail->left->db)
		ofd = open(out->tail->left->val, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		ofd = open(out->tail->left->val, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (parsed->cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(ofd, cwd, m_strlen(cwd));
		write(ofd, "\n", 1);
	}
	else
		perror("getcwd() error\n");
	return (TRUE);
}
