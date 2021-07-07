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
