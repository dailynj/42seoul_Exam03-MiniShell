/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:34 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:35 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	*m_calloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (0);
	m_memset(tmp, 0, count * size);
	return (tmp);
}

char	*m_handle_zero(void)
{
	char	*ptr;

	ptr = (char *)m_calloc(2, sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[0] = '0';
	return (ptr);
}

long long	m_atoi(char *str)
{
	int			minus;
	long long	answer;
	int			i;

	i = 0;
	minus = 1;
	answer = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			answer = answer * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (minus * answer);
}

int	m_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}
