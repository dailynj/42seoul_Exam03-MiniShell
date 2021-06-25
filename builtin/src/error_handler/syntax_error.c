#include "builtin.h"

int check_syntax()
{
	int i;
	int dquote;
	int squote;

	if (m_strchr(g_read_buf, ';') || m_strchr(g_read_buf, '`'))
		return (1);
	i = 0;
	dquote = 0;
	squote = 0;	
	while (g_read_buf[i])
	{
		if (g_read_buf[i] == '\\' && g_read_buf[i + 1])
			++i;
		else if (g_read_buf[i] == '\\' && !g_read_buf[i + 1])
			return (1);
		else if (g_read_buf[i] == '\"')
		{
			dquote = 1;
			while (g_read_buf[++i] && g_read_buf[i] != '\"')
			{
				if (g_read_buf[i] == '\\' && g_read_buf[i + 1])
					++i;
			}
			if (g_read_buf[i] != '\"')
				return (1);
			dquote = 0;
		}
		else if (g_read_buf[i] == '\'')
		{
			squote = 1;
			while (g_read_buf[++i] && g_read_buf[i] != '\'')
				;
			if (g_read_buf[i] != '\'')
				return (1);
			squote = 0;
		}
		++i;
	}
	return (dquote || squote);
}

int check_pipe()
{
	int i;
	int flag;

	i = -1;
	while(g_read_buf[++i])
	{
		flag = 0;
		if (g_read_buf[i] != '|')
			continue ;
		if (g_read_buf[i] == '|')
		{
			while (g_read_buf[++i] && g_read_buf[i] != '|')
			{
				if (g_read_buf[i] != ' ')
					flag = 1;
			}
		}
		if (flag == 0)
			return (1);
	}
	return (0);
}