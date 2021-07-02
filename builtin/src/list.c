/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:43 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:44 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_list	*new_list(char *val, int db)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	m_memset(new_node->val, 0, BUFFER_SIZE);
	m_strlcpy(new_node->val, val, m_strlen(val) + 1);
	new_node->db = db;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	init_list(t_dummy *dummy)
{
	t_list	*new_head;
	t_list	*new_tail;

	new_head = new_list("", -1);
	new_tail = new_list("", -1);
	if (!new_head || !new_tail)
		return (FALSE);
	new_head->right = new_tail;
	new_tail->left = new_head;
	dummy->head = new_head;
	dummy->tail = new_tail;
	return (TRUE);
}

int	add_list(t_list *tail, char *val, int db)
{
	t_list	*new_node;
	t_list	*tmp;

	tmp = tail;
	new_node = new_list(val, db);
	if (!new_node)
		return (FALSE);
	tmp->left->right = new_node;
	new_node->left = tmp->left;
	new_node->right = tmp;
	tmp->left = new_node;
	return (TRUE);
}



void prt_list(t_list *head)
{
	t_list *tmp;

	tmp = head->right;
	while(tmp->right)
	{
		printf("%s -> ", tmp->val);
		tmp = tmp->right;
	}
	printf("\n");
}

t_bool		history_up(int i, int hdx, t_dummy *history, char **g_read_buf)
{
	int len;
	t_list *tmp;

	tmp = history->tail;
	if (hdx == 0)
		len = m_strlen(*g_read_buf);
	else
	{
		while (--hdx >= 0)
		{
			tmp = tmp->left;
			if (tmp->left->db == -1)
				break ;
		}
		len = m_strlen(tmp->val);
	}
	if (tmp->left->db == -1)
	{
		return (FALSE);
	}
	else
	{
		m_strlcpy(*g_read_buf, tmp->left->val, m_strlen(tmp->left->val) + 1);
		while (--len >= 0 && i-- >= 0)
			write(0, "\b \b", 3);
		return (TRUE);
	}
}

t_bool		history_down(int i, int hdx, t_dummy *history, char **g_read_buf)
{
	int len;
	t_list *tmp;

	tmp = history->tail;
	while (--hdx >= 0)
	{
		tmp = tmp->left;
		if (tmp->left->db == -1)
			break ;
	}
	len = m_strlen(tmp->val);
	while (--len >= 0 && i-- >= 0)
		write(0, "\b \b", 3);
	if (tmp->right->db != -1)
		m_strlcpy(*g_read_buf, tmp->right->val, m_strlen(tmp->right->val) + 1);
	return (TRUE);
}

void	delete_val(int hdx, t_dummy *history)
{
	t_list *tmp;

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
	t_list *tmp;

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