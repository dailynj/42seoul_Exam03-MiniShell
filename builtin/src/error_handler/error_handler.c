/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:29 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:30 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_error(t_parsed *parsed, char *status)
{
	printf("minishell: %s: ", parsed->cmd[0]);
	if (!m_strncmp(status, "127", 3))
	{
		printf("%s: No such file or directory\n", parsed->cmd[2]);
		errno = 1;
	}
	else if (!m_strncmp(status, "1", 1))
	{
		printf("-%c: invalid option\n", parsed->cmd[1][1]);
		errno = 1;
	}
	else if (!m_strncmp(status, "=", 1))
	{
		printf("`=': not a valid identifier\n");
		errno = 1;
	}
}

int	ret_mesg(char *file, char *message, int ret)
{
	printf("minishell: %s: %s\n", file, message);
	return (ret);
}

int	check_print(int boo)
{
	if (boo)
		printf("minishell: Syntax error\n");
	return (boo);
}
