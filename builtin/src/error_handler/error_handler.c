#include "builtin.h"

void		print_error(t_parsed parsed, int status)
{
	g_errno = status;
	printf("bash: %s: ", parsed.cmd[0]);
	if (status == 1)
		printf("-%c: invalid option\n", parsed.cmd[1][1]);
	else if (status == 127)
		printf("%s: No such file or directory\n", parsed.cmd[2]);
}

// 지워도 되는거
void print_parsed(t_parsed parsed)
{
	printf("0 : [%s]\n", parsed.cmd[0]);
	printf("1 : [%s]\n", parsed.cmd[1]);
	printf("2 : [%s]\n", parsed.cmd[2]);
}
