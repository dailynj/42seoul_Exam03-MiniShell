/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:46 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:47 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	m_exit(t_parsed *parsed)
{
	long long	arg;

	if (parsed->cmd[1][0] != '\0')
		arg = m_atoi(parsed->cmd[1]);
	else
		arg = m_atoi(parsed->cmd[2]);
	printf("exit\n");
	if (parsed->cmd[1][0] != '\0' && !m_isnum(parsed->cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			parsed->cmd[1]);
		exit(255);
	}
	else if (parsed->cmd[2][0] != '\0' && !m_isnum(parsed->cmd[2]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			parsed->cmd[2]);
		exit(255);
	}
	exit((256 + arg) % 256);
}
