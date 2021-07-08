/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:43 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:43 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	cmd_echo_else(t_parsed *output, char *line, int *jdx, char *temp,
			int *idx)
{
	if (!output->cmd[1][0] && *idx == 1)
		++(*idx);
	temp = line + *jdx;
	while (line[*jdx] && ((line[*jdx]) != 32 || *idx != 0))
	{
		output->cmd[*idx][(line + *jdx) - temp] = line[*jdx];
		++*jdx;
	}
}

void	cmd_echo(t_parsed *output, char *line, int *jdx, int idx, int cnt)
{
	char	*temp;

	temp = 0;
	while (idx < cnt && idx < 3)
	{
		while (line[*jdx] == 32)
			++(*jdx);
		if (nnnn(line + *jdx, 0, 0, 0) > 0 && idx == 1)
		{
			m_strcpy(output->cmd[1], "-n");
			*jdx += (nnnn(line + *jdx, 0, 0, 0));
		}
		else
			cmd_echo_else(output, line, jdx, temp, &idx);
		if (check(line + *jdx))
			++cnt;
		++idx;
	}
}

void	get_cmd__one(t_parsed *output, char *line, int *jdx, int *i)
{
	while (line[*jdx] != '\0' && line[*jdx] != ' ')
	{
		output->cmd[1][++(*i)] = line[*jdx];
		++(*jdx);
	}
}

void	get_cmd_else(t_parsed *output, char *line, int *jdx)
{
	int	idx;
	int	cnt;
	int	i;

	idx = 1;
	cnt = 2;
	while (idx < cnt && idx < 3)
	{
		i = -1;
		while (line[*jdx] == 32)
			++*jdx;
		if (line[*jdx] == '-' && idx == 1)
			get_cmd__one(output, line, jdx, &i);
		else
		{
			while (line[*jdx] != '\0')
			{
				output->cmd[2][++i] = line[*jdx];
				++*jdx;
			}
		}
		if (check(line + *jdx))
			++cnt;
		++idx;
	}
}

t_parsed	*get_cmd(char *line)
{
	t_parsed	*output;
	int			i;
	int			j;

	i = -1;
	j = 0;
	output = malloc(sizeof(t_parsed));
	m_memset(output, 0, sizeof(t_parsed));
	while (line[j] == 32)
		++j;
	while (line[j] && ((line[j]) != 32) && (line[j] != '<') && (line[j] != '>'))
	{
		output->cmd[0][++i] = line[j];
		++j;
	}
	if (!m_strncmp(output->cmd[0], "echo", 4))
	{
		if (check(line + j))
			cmd_echo(output, line, &j, 1, 2);
	}
	else
		get_cmd_else(output, line, &j);
	return (output);
}
