#include "builtin.h"

void		print_error(char *cmd, char *arg, char *message)
{
	if (!arg)
		printf("%s %s\n", cmd, message);
	else
		printf("%s %s: %s\n", cmd, arg, message);
}

void print_parsed(t_parsed parsed)
{
	printf("0 : %s\n", parsed.cmd[0]);
	printf("1 : %s\n", parsed.cmd[1]);
	printf("2 : %s\n", parsed.cmd[2]);
}
