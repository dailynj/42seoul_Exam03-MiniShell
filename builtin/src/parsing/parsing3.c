/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:00 by najlee            #+#    #+#             */
/*   Updated: 2021/07/15 14:28:48 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_quote(char *read_buf, int x)
{
	int	length;

	length = 0;
	if (read_buf[x] == '\"')
	{
		if (read_buf[x + 1] == '$')
			return (length);
		while (read_buf[++x] != '\"')
		{
			++length;
		}
	}
	else if (read_buf[x] == '\'')
	{
		while (read_buf[++x] != '\'')
		{
			++length;
		}
	}
	return (length);
}

int	get_x(int *j, char *read_buf)
{
	int	x;
	int	cnt;

	x = -1;
	cnt = 0;
	if (*j)
	{
		while (read_buf[++x])
		{
			if (read_buf[x] == '|')
			{
				++cnt;
				if (cnt == *j)
				{
					++x;
					while (read_buf[++x] == ' ')
						;
					break ;
				}
			}
		}
	}
	if (x == -1)
		++x;
	return (x);
}

t_parsed	*make_parsed(char *line, char *read_buf, int *j)
{
	t_parsed	*parsed;
	int			length;
	int			x;

	parsed = get_cmd(line);
	x = get_x(j, read_buf);
	length = check_quote(read_buf, x);
	if (length > m_strlen(parsed->cmd[0]))
		m_strlcpy(parsed->cmd[0], &read_buf[x + 1], length + 1);
	return (parsed);
}
