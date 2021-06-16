#include "builtin.h"

//int pwd(char **option, char *value)
int pwd()
{
	char cwd[PATH_MAX];

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
