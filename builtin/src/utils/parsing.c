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
	if (*temp == '-' && *temp++ == 'n')
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
		while (*line == 32)
				++line;
		printf("[jump : %d]\n", nnnn(line));			
		if (nnnn(line) > 0 && idx == 1)
		{
			m_strcpy(output.cmd[1], "-n");
			line += (nnnn(line));
			// printf("|%c|", *line);
		}
		else
		{
			if (!output.cmd[1][0] && idx == 1)
				idx++;
			// printf("[idx : %d, cnt : %d]\n",idx, cnt);
			// printf("line : %s\n", line);
			temp = line;
			while (*line && ((*line) != 32 || idx != 0))
			{
				output.cmd[idx][line - temp] = *line;
				++line;
			}
		}
		
		if (check(line))
			++cnt;
		++idx;
	}
	return (output);
}
