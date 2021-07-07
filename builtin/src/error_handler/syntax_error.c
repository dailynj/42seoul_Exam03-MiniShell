/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:34 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:34 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	db_quote(char *g_read_buf, int *dquote, int *i)
{
	*dquote = 1;
	while (g_read_buf[++(*i)] && g_read_buf[*i] != '\"')
		if (g_read_buf[*i] == '\\' && g_read_buf[*i + 1])
			++i;
	if (g_read_buf[*i] != '\"')
		return (1);
	*dquote = 0;
	return (0);
}

int	check_syntax2(char *g_read_buf, int *dquote, int *squote, int i)
{
	while (g_read_buf[++i])
	{
		if (g_read_buf[i] == '\\' && g_read_buf[i + 1])
			++i;
		else if (g_read_buf[i] == '\\' && !g_read_buf[i + 1])
			return (1);
		else if (g_read_buf[i] == '\"')
		{
			if (db_quote(g_read_buf, dquote, &i) == 1)
				return (1);
		}
		else if (g_read_buf[i] == '\'')
		{
			*squote = 1;
			while (g_read_buf[++i] && g_read_buf[i] != '\'')
				;
			if (g_read_buf[i] != '\'')
				return (1);
			*squote = 0;
		}
	}
	return (0);
}

int	check_syntax(char *g_read_buf)
{
	int		dquote;
	int		squote;

	dquote = 0;
	squote = 0;
	if (m_strchr(g_read_buf, ';') || m_strchr(g_read_buf, '`'))
		return (check_print(1));
	if (check_syntax2(g_read_buf, &dquote, &squote, -1))
		return (check_print(1));
	return (check_print(dquote || squote));
}

int	check_pipe(char *g_read_buf)
{
	int	i;
	int	flag;

	i = -1;
	while (g_read_buf[++i])
	{
		flag = 0;
		if (g_read_buf[i] != '|')
			continue ;
		if (g_read_buf[i] == '|')
		{
			while (g_read_buf[++i] && g_read_buf[i] != '|')
			{
				if (g_read_buf[i] != ' ')
					flag = 1;
			}
		}
		if (flag == 0)
			return (check_print(1));
	}
	return (check_print(0));
}

int	check_redi(char *line)
{
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			if (*(line + 1) == '<' || *(line + 1) == '>')
				++line;
			++line;
			while (*line == ' ')
				++line;
			if (*line == '\0')
				return (check_print(1));
		}
		++line;
	}
	return (check_print(0));
}
