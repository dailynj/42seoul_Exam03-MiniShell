#include "builtin.h"


int m_exit(t_parsed parsed)
{
	printf("exit\n");
	reset_input_mode();
	if (parsed.cmd[1][0] != '\0')
		printf("bash: exit: %s: numeric argument required\n", parsed.cmd[1]);
	else if (!m_isnum(parsed.cmd[2]))
		printf("bash: exit: %s: numeric argument required\n", parsed.cmd[2]);
	exit(0);
}
