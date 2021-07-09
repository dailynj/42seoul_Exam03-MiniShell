/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:09 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:43:02 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	init_term(t_term *term)
{
	tcgetattr(STDIN_FILENO, &term->org_term);
	tcgetattr(STDIN_FILENO, &term->new_term);
	term->new_term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term->new_term.c_cc[VMIN] = 1;
	term->new_term.c_cc[VTIME] = 0;
}

int	reset_input_mode(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->org_term);
	return (FALSE);
}

void	set_input_mode(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
}
