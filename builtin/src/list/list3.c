#include "builtin.h"

void	print_list(int ofd, t_dummy *dummy)
{
	t_list	*tmp;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		write(ofd, tmp->val, m_strlen(tmp->val));
		write(ofd, "\n", 1);
		tmp = tmp->right;
	}
}

void	print_list_export(int ofd, t_dummy *dummy)
{
	t_list	*tmp;
	int		idx;

	tmp = dummy->head->right;
	while (tmp->db != -1)
	{
		idx = -1;
		write(ofd, "declare -x ", 11);
		while (tmp->val[++idx])
		{
			write(ofd, &tmp->val[idx], 1);
			if (tmp->val[idx] == '=')
				write(ofd, "\"", 1);
		}
		if (find_equal(tmp->val) != m_strlen(tmp->val))
			write(ofd, "\"", 1);
		write(ofd, "\n", 1);
		tmp = tmp->right;
	}
}
