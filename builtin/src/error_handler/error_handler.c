#include "builtin.h"

void		print_error(t_parsed parsed, char *status)
{
	// g_errno = status;
	printf("bash: %s: ", parsed.cmd[0]);
	if (!m_strncmp(status, "?=127", 5))
	{
		printf("%s: No such file or directory\n", parsed.cmd[2]);
		g_question = m_strdup("127");
		insert_tree(status);
	}
	else if (!m_strncmp(status, "?=1", 3))
	{
		printf("-%c: invalid option\n", parsed.cmd[1][1]);
		g_question = m_strdup("1");
		insert_tree(status);
	}
}

// 지워도 되는거
void print_parsed(t_parsed parsed)
{
	printf("0 : [%s]\n", parsed.cmd[0]);
	printf("1 : [%s]\n", parsed.cmd[1]);
	printf("2 : [%s]\n", parsed.cmd[2]);
}
