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

size_t	m_check_size(char *s, char c)
{
	size_t	cnt;
	int		i;

	cnt = 0;
	i = -1;
	if (!*s)
		return (0);
	while (*(++i + s + 1))
		if (*(i + s) != c && *(i + s + 1) == c)
			++cnt;
	return (*(s + i) != c ? cnt + 1 : cnt);
}

char		**m_free_split(char **s, int i)
{
	while (--i >= 0 && *(s + i))
	{
		free(*(s + i));
		*(s + i) = NULL;
	}
	free(s);
	s = NULL;
	return (NULL);
}

char			**m_split_char(char *s, char c)
{
	char	**ret;
	char	*from;
	int		i;

	if (!s ||
		!(ret = (char **)malloc(sizeof(char *) * (m_check_size(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			from = (char *)s;
			while (*s && *s != c)
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
