/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:42:12 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 13:42:13 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	get_buf(int tmp)
{
	if (tmp % 10 > 0)
		return ((tmp % 10) + '0');
	else
		return (-(tmp % 10) + '0');
}

int	get_tmp(int n)
{
	if (n < 0)
		return (0);
	return (-1);
}

char	get_ptr(int n, char pptr)
{
	if (n < 0)
		return ('-');
	return (pptr);
}

char	*m_itoa(int n)
{
	char	*ptr;
	char	buf[20];
	int		tmp;
	int		len;

	if (n == 0)
		return (m_handle_zero());
	tmp = n;
	len = 0;
	while (tmp)
	{
		buf[len] = get_buf(tmp);
		tmp /= 10;
		len++;
	}
	if (n < 0)
		len++;
	ptr = (char *)m_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	tmp = get_tmp(n);
	ptr[0] = get_ptr(n, ptr[0]);
	while ((++tmp) < len)
		ptr[tmp] = buf[len - 1 - tmp];
	return (ptr);
}

char	m_tolower(char s)
{
	if (s >= 65 && s <= 90)
		return (s + 32);
	return (s);
}
