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
