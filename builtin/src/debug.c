#include "builtin.h"

/***************  for debug  * *************/
void printpipe(char **pipe_str)
{
	int i = -1;
	while (*pipe_str)
	{
		printf("pipe_str %d : %s\n", ++i, *pipe_str);
		++pipe_str;
	}
}

void print_parsed(t_parsed parsed)
{
	printf("0 : [%s]\n", parsed.cmd[0]);
	printf("1 : [%s]\n", parsed.cmd[1]);
	printf("2 : [%s]\n", parsed.cmd[2]);
}
