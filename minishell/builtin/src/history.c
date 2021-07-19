/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:40:56 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:40:56 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	history_up(t_idx ihdx, t_dummy *history, char **read_buf)
{
	int		len;
	t_list	*tmp;

	tmp = history->tail;
	if (ihdx.j == 0)
		len = m_strlen(*read_buf);
	else
	{
		while (--ihdx.j >= 0)
		{
			tmp = tmp->left;
			if (tmp->left->db == -1)
				break ;
		}
		len = m_strlen(tmp->val);
	}
	if (tmp->left->db == -1)
		return (FALSE);
	else
	{
		m_strlcpy(*read_buf, tmp->left->val, m_strlen(tmp->left->val) + 1);
		while (--len >= 0 && ihdx.i-- >= 0)
			write(0, "\b \b", 3);
		return (TRUE);
	}
}

int	history_down(int idx, int hdx, t_dummy *history, char **read_buf)
{
	int		len;
	t_list	*tmp;

	tmp = history->tail;
	while (--hdx >= 0)
	{
		tmp = tmp->left;
		if (tmp->left->db == -1)
			break ;
	}
	len = m_strlen(tmp->val);
	while (--len >= 0 && idx-- >= 0)
		write(0, "\b \b", 3);
	if (tmp->right->db != -1)
		m_strlcpy(*read_buf, tmp->right->val, m_strlen(tmp->right->val) + 1);
	return (TRUE);
}

void	delete_val(int hdx, t_dummy *history)
{
	t_list	*tmp;

	tmp = history->tail;
	while (--hdx >= 0)
	{
		tmp = tmp->left;
		if (tmp->left->db == -1)
			break ;
	}
	tmp->val[m_strlen(tmp->val) - 1] = 0;
}

void	write_val(int hdx, t_dummy *history, int ch)
{
	t_list	*tmp;

	tmp = history->tail;
	while (--hdx >= 0)
	{
		tmp = tmp->left;
		if (tmp->left->db == -1)
			break ;
	}
	tmp->val[m_strlen(tmp->val)] = ch;
	tmp->val[m_strlen(tmp->val) + 1] = 0;
}
