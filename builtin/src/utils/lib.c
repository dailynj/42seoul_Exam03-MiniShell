#include "builtin.h"

int	m_strncmp(char *s1, char *s2, size_t n)
{
	if (n == 0)
		return (-1);
	while (*s1 && *s2 && n && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	*m_memset(void *dest, int value, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		*((char *)dest + i) = value;
	return (dest);
}

int		m_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// int m_strcmp(char *s1, char *s2)
// {
// 	while (*s1 != '\0' || *s2 != '\0')
// 	{
// 		if (*s1 > *s2)
// 			return 1;
// 		else if (*s1 < *s2)
// 			return -1;
// 		s1++;
// 		s2++;
// 	}
// 	return 0;
// }

char *m_strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	m_memset(dest, 0, sizeof(dest));
	while ((*dest++ = *src++) != '\0')
		;
	return tmp;
}

int find_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1); // =이 없으면
}

int m_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}
