/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:41:06 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:41:07 by najlee           ###   ########.fr       */
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

void	delete_list_head(t_dummy *dummy)
{
	t_list	*tmp;
	t_list	*del_node;

	tmp = dummy->head;
	del_node = tmp->right;
	tmp->right = tmp->right->right;
	tmp->right->left = tmp;
	free(del_node);
	del_node = 0;
}

void	free_list(t_dummy **dummy)
{
	t_dummy	**cur_node;

	cur_node = dummy;
	while ((*cur_node)->head->right->db != -1)
		delete_list_head(*dummy);
	free((*cur_node)->head);
	(*cur_node)->head = 0;
	free((*cur_node)->tail);
	(*cur_node)->tail = 0;
	free(*dummy);
	*dummy = 0;
}
