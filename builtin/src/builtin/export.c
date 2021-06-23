#include "builtin.h"

int m_export(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, 1);
	else if (parsed.cmd[2][0] >= '0' && parsed.cmd[2][0] <= '9')
		print_error(parsed, 1); // export: `1=132': not a valid identifier
	else if (parsed.cmd[2][0] != '\0')
		insert_tree(parsed.cmd[2]);
	else
		inorder_print(tree(), export);
	return (OK);
}
