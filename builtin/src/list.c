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
	int		len;
	t_list	*tmp;

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

// 넣을 장소 찾아서 넣기
int add_list_sort(t_dummy *dummy, char *val)
{
	t_list	*tmp;
	t_list	*new_node;

	tmp = dummy->head;
	while (tmp->right->db != -1)
	{
		if (m_strncmp(tmp->right->val, val, find_equal(val)) >= 0)
			break ;
		tmp = tmp->right;
	}
	if (m_strncmp(tmp->right->val, val, find_equal(val)) == 0)
		m_strlcpy(tmp->right->val, val, m_strlen(val) + 1);
	else
	{
		new_node = new_list(val, 0);
		if (!new_node)
			return (FALSE);
		++dummy->head->db;
		// tmp->right --> tmp->new_node->right
		new_node->right = tmp->right;
		tmp->right->left = new_node;
		tmp->right = new_node;
		new_node->left = tmp;
	}
	return (TRUE);
}

void print_list(t_dummy *dummy)
{
	t_list *tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		printf("--> (%s : %d)\n", tmp->val, tmp->db);
		tmp = tmp->right;
	}
}

void free_list(t_dummy **dummy)
{
	t_dummy **cur_node;

	cur_node = dummy;
	while ((*cur_node)->head->right->db != -1)
	{
		delete_list(*dummy, (*cur_node)->head->right->val);
		
		// del_node = (*cur_node)->head->;
		// *cur_node = (*cur_node)->head->right;
		// del_node->right = 0;
		// del_node->left = 0;
		// free(del_node);
	}
	free((*cur_node)->head);
	(*cur_node)->head = 0;
	free((*cur_node)->tail);
	(*cur_node)->tail = 0;
	free(*dummy);
	*dummy = 0;
}

char **make_envp(t_dummy *dummy)
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
		// printf("val : %s\n", cur_node->val);
		// printf("ret[%d] : %s\n", i, ret[i]);
		cur_node = cur_node->right;
	}
	ret[size] = 0;
	return (ret);
}

int	search_list(t_dummy *dummy, char *val)
{
	t_list *tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		if (!m_strncmp(tmp->val, val, find_equal(tmp->val)))
			return (TRUE);
		tmp = tmp->right;
	}
	return (FALSE);
}

char *m_find_env_list(t_dummy *dummy, char *val)
{
	char *ret;
	t_list *tmp;

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

int delete_list(t_dummy *dummy, char *val)
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
		del_node = tmp->right;
		tmp->right = tmp->right->right;
		tmp->right->left = tmp;
		free(del_node);
		del_node = 0;
	}
	return (TRUE);
}