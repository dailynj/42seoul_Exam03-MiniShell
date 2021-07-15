/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:47 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:48 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_real(char *buf, int idx)
{
	if (buf[idx] == '|')
		return (REAL_PIPE);
	return (0);
}

void	get_env(char **env, char *buf, int *idx)
{
	int		edx;

	edx = -1;
	(*idx)++;
	*env = malloc(BUFFER_SIZE);
	if (!*env)
		return ;
	while (buf[(*idx)] && buf[(*idx)] != ' '
		&& buf[(*idx)] != '\'' && buf[(*idx)] != '\"')
		(*env)[++edx] = buf[(*idx)++];
	--(*idx);
	(*env)[++edx] = 0;
}

int	put_env(char **temp, char *env, int tdx)
{
	char	*dirp;
	int		i;

	i = -1;
	dirp = m_find_env_list(g_env_list, env);
	if (dirp[++i])
	{
		while (dirp[i])
		{
			(*temp)[++tdx] = dirp[i];
			++i;
		}
	}
	free(dirp);
	dirp = 0;
	return (tdx);
}

void	replace_errno(int before_errno, t_idx *itdx, char *temp)
{
	char	*err;
	int		edx;

	edx = -1;
	err = m_itoa(before_errno);
	while (err[++edx])
	{
		temp[++(itdx->j)] = err[edx];
	}
	free(err);
	++itdx->i;
}
