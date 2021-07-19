/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:04:30 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:04:30 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	m_strchr(char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

size_t	m_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	while (src[i])
		++i;
	return (i);
}

size_t	m_check_size(char *s, char c)
{
	size_t	cnt;
	int		i;

	cnt = 0;
	i = -1;
	if (!s)
		return (0);
	while (*(++i + s + 1))
		if (*(i + s) != c && *(i + s + 1) == c)
			++cnt;
	if (*(s + i) != c)
		return (cnt + 1);
	return (cnt);
}

char	**m_free_split(char **s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!*s)
	{
		free(s);
		s = 0;
		return (NULL);
	}
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = 0;
	return (NULL);
}

char	**m_split_char(char *s, char c)
{
	char	**ret;
	char	*from;
	int		i;

	ret = (char **)m_calloc((m_check_size(s, c) + 1), sizeof(char *));
	if (!s || !ret)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			from = (char *)s;
			while (*s && *s != c)
				++s;
			ret[i++] = m_substr(from, 0, (s - from));
			if (!ret)
				return (m_free_split(ret));
		}
		else
			++s;
	}
	ret[i] = NULL;
	return (ret);
}
