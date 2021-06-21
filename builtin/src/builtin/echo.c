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
			// parsed.cmd[1][0] = '-';
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
	// if (!m_strncmp(parsed.cmd[1], "-n", 2))
	// {
	// 	printf("%s", parsed.cmd[2]);
	// 	return (0);
	// }
	int idx;

	idx = -1;
	if (parsed.cmd[1][++idx] == '-')
	{
		printf("option : %s\n", parsed.cmd[1]);
		while (parsed.cmd[1][++idx] == 'n')
			;
		if (parsed.cmd[1][idx] && parsed.cmd[1][idx] != 'n')
		{
			printf("%s ", parsed.cmd[1]);
			printf("%s\n", parsed.cmd[2]);
			return (0);
		}
		else
		{
			printf("%s", parsed.cmd[2]);
			return (0);
		}
	}
	printf("%s\n", parsed.cmd[2]);

	return (0);
}
