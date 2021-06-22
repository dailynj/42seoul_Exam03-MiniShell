#include "builtin.h"

int m_pwd(t_parsed parsed)
{
	char cwd[PATH_MAX];

	if (parsed.cmd[1][0] != '\0')
	{
		// invalid option 추가하기
		// 예시 bash: export: -l: invalid option
		return (ERROR);
	}
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd() error");
		return (ERROR);
	}
	return (OK);
}
