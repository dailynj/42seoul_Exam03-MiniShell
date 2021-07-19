/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:02:52 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:02:53 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	add_word(char *temp, t_parsed *parsed)
{
	if (temp[0] >= '0' && temp[0] <= '9')
		print_error(parsed, "1");
	else if (temp[0] == '=')
		print_error(parsed, "=");
	else
		add_list_sort(g_env_list, temp);
}

int	m_export(t_parsed *parsed, t_dummy *out)
{
	int		ofd;
	int		i;
	char	**temp;

	i = -1;
	temp = m_split_char(parsed->cmd[2], 32);
	if (out->tail->left->db == -1)
		ofd = 1;
	else if (out->tail->left->db)
		ofd = open(out->tail->left->val, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		ofd = open(out->tail->left->val, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (parsed->cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (parsed->cmd[2][0] != '\0')
	{
		while (temp[++i])
			add_word(temp[i], parsed);
	}
	else
		print_list_export(ofd, g_env_list);
	if (ofd != 1)
		close(ofd);
	m_free_split(temp);
	return (TRUE);
}
