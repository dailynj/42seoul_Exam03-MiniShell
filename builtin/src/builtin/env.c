#include "builtin.h"

int m_env(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
	{
		// env: illegal option -- q
		return (ERROR);
	}
	else if (parsed.cmd[2][0] != '\0')
	{
		if (!m_find_env(parsed.cmd[2][0]))
		{
			// env: PATH: No such file or directory
			return (ERROR);
		}
		else
			printf("env : %s\n", m_find_env(parsed.cmd[2][0]));
	}
	else
		inorder_print(tree(), environ);
	return (OK); // 수정
}
