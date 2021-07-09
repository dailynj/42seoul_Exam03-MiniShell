/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:42:49 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:42:49 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	sigint_handler(int err)
{
	(void)err;
}

void	sigquit_handler(int err)
{
	(void)err;
	printf("\n");
}
