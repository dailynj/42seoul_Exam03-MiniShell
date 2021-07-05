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

int		m_exit(t_parsed parsed)
{
	printf("exit\n");
	if (parsed.cmd[1][0] != '\0')
		printf("bash: exit: %s: numeric argument required\n", parsed.cmd[1]);
	else if (!m_isnum(parsed.cmd[2]))
		printf("bash: exit: %s: numeric argument required\n", parsed.cmd[2]);
	exit(errno);
}
