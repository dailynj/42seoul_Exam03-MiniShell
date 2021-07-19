/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:42:37 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:42:38 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	input_ctrlc_nl(char **buf, t_idx *ihdx, t_dummy *history, int ch)
{
	if (ch == 3)
	{
		errno = 1;
		write(1, "\n", 1);
	}
	else if (ch == '\n')
	{
		buf[0][++ihdx->i] = 0;
		buf[1][ihdx->i] = 0;
		write(1, "\n", 1);
		if (buf[0][0] != '\0')
			add_list(history->tail, buf[0], 0);
	}
}

void	init_input(char *read_buf, t_idx *ihdx, char **buf)
{
	char	*tmp_buf;

	ihdx->i = -1;
	ihdx->j = 0;
	tmp_buf = malloc(BUFFER_SIZE);
	if (tmp_buf == NULL)
		exit(1);
	m_memset(tmp_buf, 0, BUFFER_SIZE);
	m_memset(read_buf, 0, BUFFER_SIZE);
	buf[0] = read_buf;
	buf[1] = tmp_buf;
}

void	noncanonical_input(char *read_buf, t_term *term, t_dummy *history)
{
	char	*buf[2];
	int		ch;
	t_idx	ihdx;

	ch = 0;
	init_input(read_buf, &ihdx, buf);
	while (read(0, &ch, sizeof(ch)) > 0)
	{
		if (ch == 4283163 || ch == 4348699 || ch == 4479771 || ch == 4414235)
			input_updown(buf, ch, history, &ihdx);
		else if (ch == 4 || ch == '\t')
			input_ctrld(term, ihdx.i, ch);
		else if (ch == 127)
			input_backspace(buf, &ihdx, history);
		else if (ch == 3 || ch == '\n')
		{
			input_ctrlc_nl(buf, &ihdx, history, ch);
			break ;
		}
		else
			input_ch(buf, &ihdx, history, ch);
		ch = 0;
	}
	free(buf[1]);
	reset_input_mode(term);
}
