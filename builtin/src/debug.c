/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:13 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:13 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	printpipe(char **pipe_str)
{
	int	i;

	i = -1;
	while (*pipe_str)
	{
		printf("pipe_str %d : %s\n", ++i, *pipe_str);
		++pipe_str;
	}
}

void	print_parsed(t_parsed parsed)
{
	printf("0 : [%s]\n", parsed.cmd[0]);
	printf("1 : [%s]\n", parsed.cmd[1]);
	printf("2 : [%s]\n", parsed.cmd[2]);
}

void	print_list(t_dummy *dummy)
{
	t_list	*tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		printf("%s\n", tmp->val);
		tmp = tmp->right;
	}
}
