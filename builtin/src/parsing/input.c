/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:42:32 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:42:32 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	input_up(char *buf[2], t_dummy *history, t_idx *ihdx, int ch)
{
	int	k;

	if (ch == 4479771 || ch == 4414235)
		;
	else if (history_up(*ihdx, history, &buf[0]))
	{
		k = -1;
		while (buf[0][++k])
			write(1, &buf[0][k], 1);
		ihdx->i = k - 1;
		++ihdx->j;
	}
}

void	input_updown(char *buf[2], int ch, t_dummy *history, t_idx *ihdx)
{
	int	k;

	if (ch == 4348699)
	{
		if (ihdx->j == 1 && history_down(ihdx->i, ihdx->j, history, &buf[0]))
		{
			m_strlcpy(buf[0], buf[1], m_strlen(buf[1]) + 1);
			k = -1;
			while (buf[0][++k])
				write(1, &buf[0][k], 1);
			ihdx->i = k - 1;
			--ihdx->j;
		}
		else if (ihdx->j != 0 && history_down(ihdx->i, ihdx->j,
				history, &buf[0]))
		{
			k = -1;
			while (buf[0][++k])
				write(1, &buf[0][k], 1);
			ihdx->i = k - 1;
			--ihdx->j;
		}
	}
	else
		input_up(buf, history, ihdx, ch);
}

void	input_ctrld(t_term *term, int idx, int ch)
{
	if (idx == -1 && ch != '\t')
	{
		reset_input_mode(term);
		printf("exit\n");
		exit(0);
	}
}

void	input_backspace(char *buf[2], t_idx *ihdx, t_dummy *history)
{
	if (ihdx->i >= 0)
	{
		write(1, "\b \b", 3);
		buf[1][ihdx->i] = 0;
		buf[0][ihdx->i--] = 0;
		delete_val(ihdx->j, history);
	}
}

void	input_ch(char *buf[2], t_idx *ihdx, t_dummy *history, int ch)
{
	buf[0][++ihdx->i] = ch;
	buf[1][ihdx->i] = ch;
	write_val(ihdx->j, history, ch);
	write(1, &ch, 1);
}
