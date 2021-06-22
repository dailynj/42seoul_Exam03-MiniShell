#include "builtin.h"

int m_unset(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
	{
		// invalid option 추가하기
		// 예시 bash: export: -l: invalid option
		return (ERROR);
	}
	else
		delete_tree(parsed.cmd[2]);
	return (OK);
}
