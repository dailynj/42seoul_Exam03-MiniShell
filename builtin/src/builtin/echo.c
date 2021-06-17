#include "builtin.h"

int m_echo(t_parsed parsed)
{
	if (!m_strncmp(parsed.cmd[1], "-n", 2))
	{
		printf("%s", parsed.cmd[2]);
		return (0);
	}
	// error handling  따로 하기
	if (!m_strncmp(parsed.cmd[1], "-", 1))
	{
		printf("Error: 없는 옵션입니다.\n");
		return (0);
	}
	printf("%s\n", parsed.cmd[2]);

	return (0);
}
