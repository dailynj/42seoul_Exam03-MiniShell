#include "builtin.h"

int m_pwd(t_parsed parsed)
{
	char cwd[PATH_MAX];
	(void) parsed;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd() error");
		return 1;
	}
	return (0);
}
