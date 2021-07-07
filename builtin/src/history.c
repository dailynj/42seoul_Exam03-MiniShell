#include "builtin.h"

int	history_up(int i, int hdx, t_dummy *history, char **g_read_buf)
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
		return (FALSE);
	else
	{
		m_strlcpy(*g_read_buf, tmp->left->val, m_strlen(tmp->left->val) + 1);
		while (--len >= 0 && i-- >= 0)
			write(0, "\b \b", 3);
		return (TRUE);
	}
}

int	history_down(int i, int hdx, t_dummy *history, char **g_read_buf)
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
	while (--len >= 0 && i-- >= 0)
		write(0, "\b \b", 3);
	if (tmp->right->db != -1)
		m_strlcpy(*g_read_buf, tmp->right->val, m_strlen(tmp->right->val) + 1);
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
