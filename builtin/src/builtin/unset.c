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
	if (parsed->cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else
		delete_list(&g_env_list, parsed->cmd[2]);
	return (TRUE);
}
