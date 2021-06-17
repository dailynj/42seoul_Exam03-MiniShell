#include "builtin.h"

t_tree	*tree(void)
{
	static t_tree	tree;

	return (&tree);
}

void init_tree(char **env)
{
	(void) env;
	m_strcpy(tree()->val, "a=h");
	tree()->left = NULL;
	tree()->right = NULL;
	tree()->size = 0;
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
		if (m_strncmp(tmp->val, val, m_max(m_strlen(val), find_equal(tmp->val))) > 0)
		{
			ret = &(tmp->left);
			tmp = tmp->left;
		}
		else if (m_strncmp(tmp->val, val, m_max(m_strlen(val), find_equal(tmp->val))) < 0)
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
	t_tree **tmp;

	delete_node = search_tree(val);
	if (delete_node == NULL)
		return ;
	--tree()->size;
	if ((*delete_node)->right)
	{
		tmp = delete_node;
		*tmp = (*tmp)->right;
		if ((*delete_node)->left)
			(*tmp)->left = (*delete_node)->left;
	}
	else if ((*delete_node)->left)
	{
		tmp = delete_node;
		*tmp = (*tmp)->left;
	}
	free(*delete_node);
	*delete_node = 0;
}

/*
** how to free
** free_tree(tree()->right);
** free_tree(tree()->left);
*/
void free_tree(t_tree **tr)
{
	if (*tr == NULL)
		return;
	free_tree(&((*tr)->left));
	free_tree(&((*tr)->right));
	free(*tr);
	*tr = 0;
}

char*	inorder_print_node(char *val, int type)
{
	if (type >> 1) 				// environ = 2
		printf("%s\n", val);
	else 						// export = 1
	{
		printf("declare -x ");
		while (*val)
		{
			printf("%c", *val);
			if (*val == '=')
				printf("\"");
			++val;
		}
		printf("\"\n");
	}
	return (NULL);
}

int inorder_execve(t_tree *tr, char **output, int index)
{
	if (tr == NULL)
		return (index);
	index = inorder_execve(tr->left, output, index);
	output[index] = m_strdup(tr->val);
	index = inorder_execve(tr->right, output, index + 1);
	return (index);
}

void inorder_print(t_tree *tr, int type)
{
	if (tr == NULL)
		return ;
	inorder_print(tr->left, type);
	inorder_print_node(tr->val, type);
	inorder_print(tr->right, type);
}
