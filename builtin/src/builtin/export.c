#include "builtin.h"

int m_export(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
	{
		// invalid option 추가하기
		// 예시 bash: export: -l: invalid option
		return (ERROR);
	}
	else if (parsed.cmd[2][0] != '\0')
	{
		insert_tree(parsed.cmd[2]);
	}
	else
	{
		inorder_print(tree(), export);
	}
	return (OK); //	수정
}
