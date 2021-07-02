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
		return (ERROR);
	new_head->right = new_tail;
	new_tail->left = new_head;
	dummy->head = new_head;
	dummy->tail = new_tail;
	return (OK);
}

int	add_list(t_list *tail, char *val, int db)
{
	t_list	*new_node;
	t_list	*tmp;

	tmp = tail;
	new_node = new_list(val, db);
	if (!new_node)
		return (ERROR);
	tmp->left->right = new_node;
	new_node->left = tmp->left;
	new_node->right = tmp;
	tmp->left = new_node;
	return (OK);
}

// int srh_list(t_list *list, char *find)
// {
// 	t_list *tmp;

// 	tmp = list->link[1];
// 	while (tmp->link[ht()->stack[t]->val])
// 	{
// 		if (tmp->val == find)
// 			return (1);
// 		tmp = tmp->link[ht()->stack[t]->val];
// 	}
// 	return (0);
// }

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
