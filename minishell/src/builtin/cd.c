/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:25 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:26 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	m_cd_env(char *envp)
{
	char	*dirp;

	dirp = m_find_env_list(g_env_list, envp);
	return (chdir(dirp));
}

int	m_cd(t_parsed *parsed)
{
	int	result;

	if ((parsed->cmd[2][0] == '~' && (parsed->cmd[2][1] == ' '
		|| parsed->cmd[2][1] == '\0')) || (parsed->cmd[1][0] == '\0'
		&& parsed->cmd[2][0] == '\0'))
		result = m_cd_env("HOME");
	else
		result = chdir(parsed->cmd[2]);
	if (result != 0)
	{
		if (parsed->cmd[1][0] != 0)
		{
			print_error(parsed, "?=1");
			printf("cd:", NULL, "usage: cd [-L|-p] [dir]");
		}
		else
			print_error(parsed, "?=127");
	}
	return (TRUE);
}
