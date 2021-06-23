#include "builtin.h"


int m_exit(t_parsed parsed)
{
	// 전부 다 free 해주기
	if (parsed.cmd[1][0] != '\0')
	{
		// bash: exit: -n: numeric argument required
		return (ERROR);
	}
	else if (!m_isnum(parsed.cmd[2]))
	{
		// bash: exit: -n: numeric argument required
		return (ERROR);
	}
	printf("exit\n");
	exit(0);
}
