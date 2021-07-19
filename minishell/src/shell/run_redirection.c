/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:00 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:01 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*first_word(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = malloc(BUFFER_SIZE);
	tmp = m_memset(tmp, 0, BUFFER_SIZE);
	if (!line || !tmp)
		return (NULL);
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '<' && line[i] != '>'
			&& line[i] != '\0')
		{
			while (line[i] != ' ' && line[i] != '<' && line[i] != '>'
				&& line[i] != '\0')
			{
				tmp[++j] = line[i];
				++i;
			}
			return (tmp);
		}
	}
	return (tmp);
}

void	fill_list(char *line, char ch, t_dummy *std)
{
	char	*tmp;
	int		idx;

	idx = 0;
	while (line[idx])
	{
		if (line[idx] == ch)
		{
			if (line[idx + 1] == ch)
			{
				++idx;
				tmp = first_word(line + idx);
				add_list(std->tail, tmp, 1);
			}
			else
			{
				tmp = first_word(line + idx);
				add_list(std->tail, tmp, 0);
			}
			free(tmp);
		}
		++idx;
	}
}

int	core_cmd2(char *line, int *idx)
{
	if (line[*idx + 1] == '<' || line[*idx + 1] == '>')
		++(*idx);
	++(*idx);
	while (line[*idx] == ' ')
		++(*idx);
	while (line[*idx] != ' ' && line[*idx] != '\0')
		++(*idx);
	while (line[*idx] == ' ' && line[*idx] != '\0')
		++(*idx);
	if (line[*idx] == '\0')
		return (1);
	if (line[*idx] == '<' || line[*idx] == '>')
		return (2);
	return (0);
}

char	*core_cmd(char *line)
{
	char	*temp;
	int		ret;
	t_idx	itdx;

	itdx.j = -1;
	itdx.i = -1;
	temp = malloc(BUFFER_SIZE);
	m_memset(temp, 0, BUFFER_SIZE);
	if (!temp)
		return (NULL);
	while (line[++itdx.i])
	{
		if (line[itdx.i] == '<' || line[itdx.i] == '>')
		{
			ret = core_cmd2(line, &itdx.i);
			if (ret == 1)
				break ;
			else if (ret == 2)
				--itdx.i;
		}
		else
			temp[++itdx.j] = line[itdx.i];
	}
	temp[++itdx.j] = 0;
	return (temp);
}

char	*join_parsed(t_parsed *parsed)
{
	char	*ret;
	int		cnt;
	int		idx;
	int		rdx;

	cnt = -1;
	rdx = -1;
	ret = malloc(BUFFER_SIZE);
	while (++cnt < 3)
	{
		idx = -1;
		while (parsed->cmd[cnt][++idx])
		{
			ret[++rdx] = parsed->cmd[cnt][idx];
		}
		ret[++rdx] = ' ';
	}
	ret[++rdx] = 0;
	return (ret);
}
