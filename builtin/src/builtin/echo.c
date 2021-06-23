#include "builtin.h"

int nnnn(char *line)
{
	int idx;
	int ret;
	int flag;

	flag = 0;
	idx = 0;
	ret = 0;
	if (line[idx] != '-')
		return (0);
	while (line[idx])
	{
		if (line[idx] == '-')
		{
			++idx;
			if (!line[idx])
				break;
			while (line[idx] == 'n')
			{
				++idx;
				flag = 1;
			}
		}
		if (flag && (line[idx] == 32 || !line[idx]))
			ret = idx;
		else
			return (ret);
		++idx;
		flag = 0;
	}
	return (ret);
}

int m_echo(t_parsed parsed)
{
	if (!m_strncmp(parsed.cmd[1], "-n", 2))
		printf("%s", parsed.cmd[2]);
	else
		printf("%s\n", parsed.cmd[2]);
	return (OK);
}
