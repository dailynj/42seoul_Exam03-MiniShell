/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:34 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:35 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*m_strdup(char *src)
{
	char	*dest;
	size_t	len;

	if (!src)
		return (NULL);
	len = m_strlen(src);
	if (!(dest = (char *)malloc(len + 1)))
		return (NULL);
	m_strlcpy(dest, src, len + 1);
	return ((char *)dest);
}

int		m_arrsize(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

char *m_substr(char *s, unsigned int start, size_t len)
{
	char *dest;

	
	if (!s || !(dest = (char *)malloc(len + 1)))
		return (NULL);
	if ((int)start >= m_strlen(s) ||
		!(m_strlcpy(dest, s + start, len + 1)))
		dest[0] = '\0';
	return (dest);
}

char	*m_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = m_strlen(s1);
	j = m_strlen(s2);
	dest = (char *)malloc(i + j + 1);
	if (!dest)
		return (NULL);
	m_strlcpy(dest, s1, i + 1);
	m_strlcpy(dest + i, s2, j + 1);
	return (dest);
}

int		m_isnum(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		++i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	*m_calloc(size_t count, size_t size)
{
	char *tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (0);
	m_memset(tmp, 0, count * size);
	return (tmp);
}

char	*m_handle_zero(void)
{
	char	*ptr;

	if (!(ptr = (char *)m_calloc(2, sizeof(char))))
		return (NULL);
	ptr[0] = '0';
	return (ptr);
}

char		*m_itoa(int n)
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
		buf[len] = (tmp % 10 > 0) ? (tmp % 10) + '0' : -(tmp % 10) + '0';
		tmp /= 10;
		len++;
	}
	if (n < 0)
		len++;
	if (!(ptr = (char *)m_calloc(len + 1, sizeof(char))))
		return (NULL);
	tmp = (n < 0) ? 0 : -1;
	ptr[0] = (n < 0) ? '-' : ptr[0];
	while ((++tmp) < len)
		ptr[tmp] = buf[len - 1 - tmp];
	return (ptr);
}

long long		m_atoi(char *str)
{
	int	minus;
	long long answer;
	int	i;

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