#include "builtin.h"

int m_pwd(t_parsed parsed)
{
	char cwd[PATH_MAX];

	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, "?=1");
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(g_fds, cwd, m_strlen(cwd));
		write(g_fds, "\n", 1);
		// printf("%s\n", cwd);
	}
	else
		perror("getcwd() error\n");
	return (OK);
}
