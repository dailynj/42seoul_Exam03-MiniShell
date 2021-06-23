#include "builtin.h"

char	*m_strdup(char *src)
{
	char	*dest;
	size_t	len;

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
			return (ERROR);
		++i;
	}
	return (OK);
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

// int			find_str(char *str, char *to_find, int n)
// {
// 	str += n;
// 	while (*to_find)
// 	{
// 		if (*str != *to_find)
// 			return (0);
// 		str++;
// 		to_find++;
// 	}
// 	return (1);
// }

// char		*ft_strnstr(char *str, char *to_find, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!*to_find)
// 		return ((char *)str);
// 	if (!n)
// 		return (0);
// 	if (!*str)
// 		return (0);
// 	while ((str[i] != 0) && (i <= (n - ft_strlen(to_find))))
// 	{
// 		if (find_str(str, to_find, i) == 1)
// 			return ((char *)str + i);
// 		i++;
// 	}
// 	return (0);
// }
