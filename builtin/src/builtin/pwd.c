#include "builtin.h"

int m_pwd(t_parsed parsed)
{
	char cwd[PATH_MAX];
	(void) parsed; // 혹시 옵션 들어오면 에러 메세지 보내기!

	if (getcwd(cwd, sizeof(cwd)) != NULL)
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
