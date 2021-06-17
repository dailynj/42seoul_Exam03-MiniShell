#include "builtin.h"

int check(char *line)
{
	char *temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp)
		return (1);
	return (0);
}

int nooption(char *line)
{
	char *temp;

	temp = line;
	while (*temp == 32)
		++temp;
	if (*temp == '-')
		return (0);
	return (1);
}

t_parsed get_cmd(char *line)
{
	t_parsed output;
	char *temp;
	int idx;
	int cnt;

	idx = 0;
	cnt = 1;
	m_memset(&output, 0, sizeof(t_parsed));
	while (idx < cnt && idx < 3)
	{
		if (nooption(line) && idx == 1)
			++idx;
		while (*line == 32)
			++line;
		temp = line;
		while (*line && (*line) != 32)
		{
			output.cmd[idx][line - temp] = *line;
			++line;
		}
		if(check(line))
			++cnt;
		++idx;
	}
	return (output);
}
