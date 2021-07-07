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

void	cmd_echo_else(t_parsed *output, char **line, char *temp, int *idx)
{
	if (!output->cmd[1][0] && *idx == 1)
		++(*idx);
	temp = *line;
	while (**line && ((**line) != 32 || *idx != 0))
	{
		output->cmd[*idx][*line - temp] = **line;
		++*line;
	}
}

void	cmd_echo(t_parsed *output, char **line, int idx, int cnt)
{
	char	*temp;

	temp = 0;
	while (idx < cnt && idx < 3)
	{
		while (**line == 32)
			++*line;
		if (nnnn(*line, 0, 0, 0) > 0 && idx == 1)
		{
			m_strcpy(output->cmd[1], "-n");
			*line += (nnnn(*line, 0, 0, 0));
		}
		else
			cmd_echo_else(output, line, temp, &idx);
		if (check(*line))
			++cnt;
		++idx;
	}
}

void	get_cmd__one(t_parsed *output, char **line, int *i)
{
	while (**line != '\0' && **line != ' ')
	{
		output->cmd[1][++(*i)] = **line;
		++(*line);
	}
}

void	get_cmd_else(t_parsed *output, char **line)
{
	int	idx;
	int	cnt;
	int	i;

	idx = 1;
	cnt = 2;
	while (idx < cnt && idx < 3)
	{
		i = -1;
		while (**line == 32)
			++*line;
		if (**line == '-' && idx == 1)
			get_cmd__one(output, line, &i);
		else
		{
			while (**line != '\0')
			{
				output->cmd[2][++i] = **line;
				++*line;
			}
		}
		if (check(*line))
			++cnt;
		++idx;
	}
}

t_parsed	get_cmd(char *line)
{
	t_parsed	output;
	int			i;

	i = -1;
	m_memset(&output, 0, sizeof(t_parsed));
	while (*line == 32)
		++line;
	while (*line && ((*line) != 32) && (*line != '<') && (*line != '>'))
	{
		output.cmd[0][++i] = *line;
		++line;
	}
	if (!m_strncmp(output.cmd[0], "echo", 4))
	{
		if (check(line))
			cmd_echo(&output, &line, 1, 2);
	}
	else
		get_cmd_else(&output, &line);
	return (output);
}
