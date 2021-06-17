#include "builtin.h"

int		m_strchr(char *s, int c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

size_t			m_strlcpy(char *dst, char *src, size_t dstsize)
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

size_t			m_check_size(char *s, char *delim)
{
	size_t	cnt;
	int		i;

	cnt = 0;
	i = -1;
	if (!*s)
		return (0);
	while (*(++i + s + 1))
		if (!m_strchr(delim, *(i + s)) && m_strchr(delim, *(i + s + 1)))
			++cnt;
	return (!m_strchr(delim, *(s + i)) ? cnt + 1 : cnt);
}

char			**m_free_split(char **s, int i)
{
	if (s == NULL)
		return (NULL);
	while (--i >= 0 && *(s + i))
	{
		free(*(s + i));
		*(s + i) = NULL;
	}
	free(s);
	s = NULL;
	return (NULL);
}

char			*m_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s || !(dest = (char *)malloc(len + 1)))
		return (NULL);
	if ((int)start >= m_strlen(s) ||
			!(m_strlcpy(dest, s + start, len + 1)))
		dest[0] = '\0';
	return (dest);
}

char			**m_split(char *s, char *delim)
{
	char	**ret;
	char	*from;
	int		i;

	if (!s ||
		!(ret = malloc(sizeof(char *) * (m_check_size(s, delim) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (!m_strchr(delim, *s))
		{
			from = (char *)s;
			while (*s && !m_strchr(delim, *s))
				++s;
			if (!(ret[i++] = m_substr(from, 0, (s - from))))
				return (m_free_split(ret, i));
		}
		else
			++s;
	}
	ret[i] = NULL;
	return (ret);
}
