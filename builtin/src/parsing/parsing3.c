#include "builtin.h"

int	check_quote(char *read_buf, int x)
{
	int	length;

	length = 0;
	if (read_buf[x] == '\"')
	{
		while (read_buf[++x] != '\"')
		{
			++length;
		}
	}
	else if (read_buf[x] == '\'')
	{
		while (read_buf[++x] != '\'')
		{
			++length;
		}
	}
	return (length);
}

t_parsed	*make_parsed(char *line, char *read_buf, int *j)
{
	t_parsed	*parsed;
	int			length;
	int			x;
	int			cnt;

	x = -1;
	cnt = 0;
	parsed = get_cmd(line);
	if (*j)
	{
		while (read_buf[++x])
		{
			if (read_buf[x] == '|')
			{
				++cnt;
				if (cnt == *j)
					break ;
			}
		}
	}
	length = check_quote(read_buf, ++x);
	if (length > m_strlen(parsed->cmd[0]))
		m_strlcpy(parsed->cmd[0], &read_buf[x + 1], length + 1);
	return (parsed);
}
