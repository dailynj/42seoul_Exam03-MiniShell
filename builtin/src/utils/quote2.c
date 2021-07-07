/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:47 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:48 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	replace_env_dbquote(char *g_read_buf, char *temp, t_itdx *itdx)
{
	char	*env;

	while (g_read_buf[++(itdx->i)] && g_read_buf[itdx->i] != '\"')
	{
		if (g_read_buf[itdx->i] == '\\' && g_read_buf[itdx->i + 1]
			&& g_read_buf[itdx->i + 1] == '\\')
			temp[++(itdx->t)] = g_read_buf[++(itdx->i)];
		else if (g_read_buf[itdx->i] == '\\' && g_read_buf[itdx->i + 1])
		{
			temp[++(itdx->t)] = g_read_buf[itdx->i];
			temp[++(itdx->t)] = g_read_buf[++(itdx->i)];
		}
		else if (g_read_buf[itdx->i] == '$')
		{
			get_env(&env, g_read_buf, itdx->i);
			itdx->t = put_env(&temp, env, itdx->t);
			free(env);
		}
		else
			temp[++(itdx->t)] = g_read_buf[itdx->i];
	}
}

void	replace_dollar(char *g_read_buf, char *env, t_itdx *itdx, char *temp)
{
	get_env(&env, g_read_buf, itdx->i);
	itdx->t = put_env(&temp, env, itdx->t);
	free(env);
}

void	replace_env_else(char *g_read_buf, char *temp,
		t_itdx *itdx, int before_errno)
{
	char	*env;

	if (g_read_buf[itdx->i] == ' ')
	{
		temp[++(itdx->t)] = ' ';
		while (g_read_buf[itdx->i + 1] == ' ')
			++(itdx->i);
	}
	else if (g_read_buf[itdx->i] == '$')
	{
		if (g_read_buf[itdx->i + 1] == '?')
		{
			++(itdx->i);
			replace_errno(before_errno, itdx, temp);
		}
		else
			replace_dollar(g_read_buf, env, itdx, temp);
	}
	else if (check_real(g_read_buf, itdx->i))
		temp[++(itdx->t)] = check_real(g_read_buf, itdx->i);
	else
		temp[++(itdx->t)] = g_read_buf[itdx->i];
}

int	replace_env(char *g_read_buf, int before_errno, t_itdx *itdx)
{
	char	*temp;

	temp = m_calloc(BUFFER_SIZE, 1);
	if (!temp)
		return (FALSE);
	while (g_read_buf[++itdx->i])
	{
		if (g_read_buf[itdx->i] == '\\' && g_read_buf[itdx->i + 1])
			temp[++itdx->t] = g_read_buf[++itdx->i];
		else if (g_read_buf[itdx->i] == '\"')
			replace_env_dbquote(g_read_buf, temp, itdx);
		else if (g_read_buf[itdx->i] == '\'')
		{
			while (g_read_buf[++itdx->i] && g_read_buf[itdx->i] != '\'')
				temp[++itdx->t] = g_read_buf[itdx->i];
		}
		else
			replace_env_else(g_read_buf, temp, itdx, before_errno);
	}
	m_memset(g_read_buf, 0, BUFFER_SIZE);
	m_strlcpy(g_read_buf, temp, BUFFER_SIZE);
	free(temp);
	temp = 0;
	return (TRUE);
}
