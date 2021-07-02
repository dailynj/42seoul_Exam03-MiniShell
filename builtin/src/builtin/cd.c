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

int		m_cd_up(void)
{
	char	cwd[PATH_MAX];
	int		idx;

	getcwd(cwd, sizeof(cwd));
	idx = m_strlen(cwd);
	while (--idx >= 0)
	{
		if (cwd[idx] == '/')
		{
			cwd[idx] = '\0';
			break ;
		}
		cwd[idx] = '\0';
	}
	return (chdir(cwd));
}

int		m_cd_env(char *envp)
{
	char	*dirp;
	t_tree	**output;

	output = search_tree(envp);
	if (output == NULL)
		return (1);
	envp = (*output)->val;
	while (*envp)
	{
		if (*envp == '=')
		{
			dirp = ++envp;
			break ;
		}
		++envp;
	}
	return (chdir(dirp));
}

int		m_cd(t_parsed parsed)
{
	int	result;

	if (parsed.cmd[2][0] == '.' && parsed.cmd[2][1] == '.' && (parsed.cmd[2][2] == ' ' || parsed.cmd[2][2] == '\0'))
	{
		result = m_cd_up();
	}
	else if (parsed.cmd[2][0] == '.' && (parsed.cmd[2][1] == ' ' || parsed.cmd[2][1] == '\0'))
		result = 0;
	else if (parsed.cmd[2][0] == '$')
	{
		result = m_cd_env(&parsed.cmd[2][1]);
	}
	else if ((parsed.cmd[2][0] == '~' && (parsed.cmd[2][1] == ' ' || parsed.cmd[2][1] == '\0'))
				|| (parsed.cmd[1][0] == '\0' && parsed.cmd[2][0] == '\0'))
	{
		result = m_cd_env("HOME");
	}
	else
		result = chdir(parsed.cmd[2]);
	if (result != 0)
	{
		if (parsed.cmd[1][0] != 0)
		{
			print_error(parsed, "?=1");
			printf("cd:", NULL, "usage: cd [-L|-p] [dir]");
		}
		else
			print_error(parsed, "?=127");
	}
	return (TRUE);
}
