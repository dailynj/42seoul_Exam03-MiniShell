/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:43 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:43 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int check(char *line)
{
	char *temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp)
		return (1);
	return (0);
}

int nooption(char *line)
{
	char *temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp == '-' && *temp++ == 'n')
		return (0);
	return (1);
}

void cmd_echo(t_parsed *output, char *line)
{
	char *temp = 0;
	int idx;
	int cnt;

	idx = 1;
	cnt = 2;
	while (idx < cnt && idx < 3)
	{
		while (*line == 32)
			++line;
		if (nnnn(line, 0, 0, 0) > 0 && idx == 1)
		{
			m_strcpy(output->cmd[1], "-n");
			line += (nnnn(line, 0, 0, 0));
		}
		else
		{
			if (!output->cmd[1][0] && idx == 1)
				idx++;
			temp = line;
			while (*line && ((*line) != 32 || idx != 0))
			{
				output->cmd[idx][line - temp] = *line;
				++line;
			}
		}
		if (check(line))
			++cnt;
		++idx;
	}
}

void cmd_else(t_parsed *output, char *line)
{
	int idx;
	int cnt;
	int i;

	idx = 1;
	cnt = 2;
	while (idx < cnt && idx < 3)
	{
		i = -1;
		while (*line == 32)
				++line;
		if (*line == '-' && idx == 1)
		{
			while(*line != '\0' && *line != ' ')
			{
				output->cmd[1][++i] = *line;
				++line;
			}
		}
		else
		{
			while(*line != '\0')
			{
				output->cmd[2][++i] = *line;
				++line;
			}
		}
		if (check(line))
			++cnt;
		++idx;
	}
}

t_parsed get_cmd(char *line)
{
	t_parsed output;
	int i;

	i = -1;
	m_memset(&output, 0, sizeof(t_parsed));
	while (*line == 32)
		++line;
	while (*line && ((*line) != 32) && (*line !=  '<') && (*line != '>'))
	{
		output.cmd[0][++i] = *line;
		++line;
	}
	if (!m_strncmp(output.cmd[0], "echo", 4))
	{
		if (check(line))
		cmd_echo(&output, line);
	}
	else
	{
		cmd_else(&output, line);
	}
	return (output);
}
