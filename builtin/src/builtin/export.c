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

int m_export(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (parsed.cmd[2][0] >= '0' && parsed.cmd[2][0] <= '9')
		print_error(parsed, "?=1");
	else if (parsed.cmd[2][0] != '\0')
		insert_tree(parsed.cmd[2]);
	else
		inorder_print(tree(), export);
	return (OK);
}
