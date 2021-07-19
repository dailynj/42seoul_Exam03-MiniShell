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

int	check(char *line)
{
	char	*temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp)
		return (1);
	return (0);
}

int	nooption(char *line)
{
	char	*temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp == '-' && *temp++ == 'n')
		return (0);
	return (1);
}
