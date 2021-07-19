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
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	m_strlcpy(dest, src, len + 1);
	return ((char *)dest);
}

int	m_arrsize(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

char	*m_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;

	dest = (char *)malloc(len + 1);
	if (!s || !dest)
		return (NULL);
	if ((int)start >= m_strlen(s)
		|| !(m_strlcpy(dest, s + start, len + 1)))
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

int	m_isnum(char *str)
{
	int	i;

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
