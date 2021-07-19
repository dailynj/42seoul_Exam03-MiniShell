/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:06 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:06 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	m_unset(t_parsed *parsed)
{
	char	**temp;
	int		i;

	i = -1;
	temp = m_split_char(parsed->cmd[2], 32);
	if (parsed->cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else
	{
		while (temp[++i])
		{
			delete_list(g_env_list, temp[i]);
		}
	}
	m_free_split(temp);
	return (TRUE);
}
