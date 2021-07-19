/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:41:11 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:41:12 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	add_list_sort(t_dummy *dummy, char *val)
{
	t_list	*tmp;
	t_list	*new_node;

	tmp = dummy->head;
	while (tmp->right->db != -1
		&& m_strncmp(tmp->right->val, val, find_equal(val)) < 0)
		tmp = tmp->right;
	if (m_strncmp(tmp->right->val, val, find_equal(val)) == 0)
	{
		if (find_equal(val) != m_strlen(val))
			m_strlcpy(tmp->right->val, val, m_strlen(val) + 1);
	}
	else
	{
		new_node = new_list(val, 0);
		if (!new_node)
			return (FALSE);
		++dummy->head->db;
		new_node->right = tmp->right;
		tmp->right->left = new_node;
		tmp->right = new_node;
		new_node->left = tmp;
	}
	return (TRUE);
}

char	**make_envp(t_dummy *dummy)
{
	char	**ret;
	t_list	*cur_node;
	int		size;
	int		i;

	i = -1;
	cur_node = dummy->head->right;
	size = dummy->head->db + 1;
	ret = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
	{
		ret[i] = m_strdup(cur_node->val);
		cur_node = cur_node->right;
	}
	ret[size] = 0;
	return (ret);
}

int	search_list(t_dummy *dummy, char *val)
{
	t_list	*tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		if (!m_strncmp(tmp->val, val, find_equal(tmp->val)))
			return (TRUE);
		tmp = tmp->right;
	}
	return (FALSE);
}

char	*m_find_env_list(t_dummy *dummy, char *val)
{
	char		*ret;
	t_list		*tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		if (!m_strncmp(tmp->val, val, find_equal(tmp->val)))
		{
			ret = m_strdup(&tmp->val[find_equal(tmp->val) + 1]);
			return (ret);
		}
		tmp = tmp->right;
	}
	return (NULL);
}

int	delete_list(t_dummy *dummy, char *val)
{
	t_list	*tmp;
	t_list	*del_node;

	tmp = dummy->head;
	while (tmp->right->db != -1)
	{
		if (m_strncmp(tmp->right->val, val, find_equal(val)) >= 0)
			break ;
		tmp = tmp->right;
	}
	if (m_strncmp(tmp->right->val, val, find_equal(val)) == 0)
	{
		--dummy->head->db;
		del_node = tmp->right;
		tmp->right = tmp->right->right;
		tmp->right->left = tmp;
		free(del_node);
		del_node = 0;
	}
	return (TRUE);
}
