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

void	replace_env_dbquote(char *read_buf, char *temp, t_idx *itdx)
{
	char	*env;

	while (read_buf[++(itdx->i)] && read_buf[itdx->i] != '\"')
	{
		if (read_buf[itdx->i] == '\\' && read_buf[itdx->i + 1]
			&& read_buf[itdx->i + 1] == '\\')
			temp[++(itdx->j)] = read_buf[++(itdx->i)];
		else if (read_buf[itdx->i] == '\\' && read_buf[itdx->i + 1])
		{
			temp[++(itdx->j)] = read_buf[itdx->i];
			temp[++(itdx->j)] = read_buf[++(itdx->i)];
		}
		else if (read_buf[itdx->i] == '$')
		{
			get_env(&env, read_buf, &itdx->i);
			itdx->j = put_env(&temp, env, itdx->j);
			free(env);
		}
		else
			temp[++(itdx->j)] = read_buf[itdx->i];
	}
}

void	replace_dollar(char *read_buf, t_idx *itdx, char *temp)
{
	char	*env;

	get_env(&env, read_buf, &itdx->i);
	itdx->j = put_env(&temp, env, itdx->j);
	free(env);
}

void	replace_env_else(char *read_buf, char *temp,
		t_idx *itdx, int before_errno)
{
	if (read_buf[itdx->i] == ' ')
	{
		temp[++(itdx->j)] = ' ';
		while (read_buf[itdx->i + 1] == ' ')
			++(itdx->i);
	}
	else if (read_buf[itdx->i] == '$')
	{
		if (read_buf[itdx->i + 1] == '?')
			replace_errno(before_errno, itdx, temp);
		else
			replace_dollar(read_buf, itdx, temp);
	}
	else if (check_real(read_buf, itdx->i))
		temp[++(itdx->j)] = check_real(read_buf, itdx->i);
	else
		temp[++(itdx->j)] = read_buf[itdx->i];
}

int	replace_env(char *read_buf, int before_errno, t_idx *itdx)
{
	char	*temp;

	temp = m_calloc(BUFFER_SIZE, 1);
	if (!temp)
		return (FALSE);
	while (read_buf[++itdx->i])
	{
		if (read_buf[itdx->i] == '\\' && read_buf[itdx->i + 1])
			temp[++itdx->j] = read_buf[++itdx->i];
		else if (read_buf[itdx->i] == '\"')
			replace_env_dbquote(read_buf, temp, itdx);
		else if (read_buf[itdx->i] == '\'')
		{
			while (read_buf[++itdx->i] && read_buf[itdx->i] != '\'')
				temp[++itdx->j] = read_buf[itdx->i];
		}
		else
			replace_env_else(read_buf, temp, itdx, before_errno);
	}
	m_memset(read_buf, 0, BUFFER_SIZE);
	m_strlcpy(read_buf, temp, BUFFER_SIZE);
	free(temp);
	temp = 0;
	return (TRUE);
}
