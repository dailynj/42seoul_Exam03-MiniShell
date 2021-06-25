#include "builtin.h"

int m_env(t_parsed parsed)
{
	if (m_find_env("PATH") == NULL)
		return (OK);
	if (parsed.cmd[1][0] != '\0')
		print_error(parsed,1);
	else if (parsed.cmd[2][0] != '\0')
	{
		if (!m_find_env(&parsed.cmd[2][0]))
			print_error(parsed, 127);
		else
			// write(g_fds[1], parsed.cmd[2], m_strlen(parsed.cmd[2]));
			printf("env : %s\n", m_find_env(&parsed.cmd[2][0]));
	}
	else
		inorder_print(tree(), environ);
	return (OK); // 수정
}
