/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:12 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:13 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_tree	*tree(void)
{
	static t_tree	tree;

	return (&tree);
}

void init_tree(char **env)
{
	m_strcpy(tree()->val, "5=h");
	tree()->left = NULL;
	tree()->right = NULL;
	tree()->size = 0;
	while (*env)
	{
		insert_tree(*env);
		++env;
	}
	errno = 0;
}

t_tree *new_node(char *val)
{
	t_tree	*new_n;

	new_n = malloc(sizeof(t_tree));
	if (!new_n)
		exit(1); // need error handling
	m_strcpy(new_n->val, val);
	new_n->size = m_strlen(val);
	new_n->left = 0;
	new_n->right = 0;
	return (new_n);
}

void insert_tree(char *val)
{
	t_tree	*tmp;

	++tree()->size;
	tmp = tree();
	while (1)
	{
		if (m_strncmp(tmp->val, val, find_equal(val)) > 0)
		{
			if (!tmp->left && (tmp->left = new_node(val)))
				return ;
			tmp = tmp->left;
		}
		else if (m_strncmp(tmp->val, val, find_equal(val)) < 0)
		{
			if (!tmp->right && (tmp->right = new_node(val)))
				return ;
			tmp = tmp->right;
		}
		else
		{
			m_strcpy(tmp->val, val);
			--tree()->size;
			return ;
		}
	}
}

t_tree **search_tree(char *val)
{
	t_tree *tmp;
	t_tree **ret;

	tmp = tree();
	while (tmp)
	{
		if (m_strncmp(tmp->val, val, find_equal(tmp->val)) > 0)
		{
			ret = &(tmp->left);
			tmp = tmp->left;
		}
		else if (m_strncmp(tmp->val, val, find_equal(tmp->val)) < 0)
		{
			ret = &(tmp->right);
			tmp = tmp->right;
		}
		else
			return (ret);
	}
	return (NULL);
}

void delete_tree(char *val)
{
	t_tree **delete_node;
	t_tree **free_node;
	t_tree *tmp;
	char backup[BUFFER_SIZE];

	delete_node = search_tree(val);
	if (delete_node == NULL)
		return ;
	--tree()->size;
	tmp = *delete_node;
	if ((*delete_node)->right)
	{
		tmp = (*delete_node)->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		m_strlcpy(backup, tmp->val, BUFFER_SIZE);
	}
	else if ((*delete_node)->left)
	{
		tmp = (*delete_node)->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		m_strlcpy(backup, tmp->val, BUFFER_SIZE);
	}
	free_node = search_tree(backup);
	free(*free_node);
	*free_node = 0;
	m_strlcpy((*delete_node)->val, backup, BUFFER_SIZE);
}


void free_tree(void)
{
	if (tree()->left == NULL && tree()->right == NULL)
		return ;
	while(tree()->left)
		delete_tree(tree()->left->val);
	while(tree()->right)
		delete_tree(tree()->right->val);
}

char*	inorder_print_node(char *val, int type, int out_fds)
{
	int isequal;

	isequal = val[find_equal(val)] == '=' ? 1 : 0;
	if (val == tree()->val)
		return (NULL);
	if (type >> 1) // environ = 2
	{
		if (m_strchr(val, '='))
		{
			write(out_fds, val, m_strlen(val));
			write(out_fds, "\n", 1);
		}
	}
	else 						// export = 1
	{
		write(out_fds, "declare -x ", 11);
		while (*val)
		{
			write(out_fds, val, 1);
			if (*val == '=')
				write(out_fds, "\"", 1);
			++val;
		}
		if (isequal)
			write(out_fds, "\"", 1);
		write(out_fds, "\n", 1);
	}
	return (NULL);
}

int inorder_execve(t_tree *tr, char ***output, int index)
{
	if (tr == NULL)
		return (index);
	index = inorder_execve(tr->left, output, index);
	if (&tr->val != &tree()->val)
		(*output)[index] = m_strdup(tr->val);
	index = inorder_execve(tr->right, output, index + 1);
	return (index);
}

void inorder_print(t_tree *tr, int type, int out_fds)
{
	if (tree()->size == 0)
		return ;
	if (tr == NULL)
		return ;
	inorder_print(tr->left, type, out_fds);
	inorder_print_node(tr->val, type, out_fds);
	inorder_print(tr->right, type, out_fds);
}
