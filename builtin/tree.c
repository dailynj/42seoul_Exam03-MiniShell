#include "builtin.h"

t_tree	*tree(void)
{
	static t_tree	tree;

	return (&tree);
}

void init_tree(char **env)
{
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
		{
			return (ret);
		}
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
	if (!(*delete_node)->left && !(*delete_node)->right)
	{
		free(*delete_node);
		*delete_node = 0;
	}
	else if ((*delete_node)->right)
	{
		tmp = delete_node;
		*delete_node = (*delete_node)->right;
		if ((*tmp)->left)
			(*delete_node)->left = (*tmp)->left;
		free(*tmp);
		*tmp = 0;
	}
	else
	{
		tmp = delete_node;
		*delete_node = (*delete_node)->left;
		free(*tmp);
		*tmp = 0;
	}
}

// free_tree(tree()->left);
// free_tree(tree()->right);
void free_tree(t_tree **tr)
{
	if (*tr == NULL)
		return;
	free_tree(&((*tr)->left));
	free_tree(&((*tr)->right));
	free(*tr);
	*tr = 0;
}

void print_tree(int type, char *val)
{
	if (type >> 1) // env
		printf("%s\n", val);
	else // export
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
}

// 짜야할거....tree ->char** 로 만들기
// char **arr_for_execve()
// {
// 	// tree()->size; node 개수
// 	char **ret;
// 	int idx;

// 	if (tree()->size == 0)
// 		return (NULL);
// 	if (!(ret = (char **)malloc(sizeof(char *) * tree()->size)))
// 		exit(0); // error handle 하기
// 	idx = -1;
// 	while (++idx < tree()->size)
// 	{
// 		ret[idx] = (char *)malloc()
// 	}
// 	return (ret);
// }

char* inorder_tree(int type, t_tree *tr)
{
	if (!type)
	{
		// return (arr_for_execve());
		return (NULL);
	}
	else
	{
		print_tree(type, tr->val);
		return (NULL);
	}
}

void inorder(int type, t_tree *tr)
{
	if (tr == NULL)
		return;
	inorder(type, tr->left);
	inorder_tree(type, tr);
	inorder(type, tr->right);
}
