#include "builtin.h"

int m_unset(t_parsed parsed)
{
	if (parsed.cmd[1][0] != '\0')
		print_error(parsed, 1);
	else
		delete_tree(parsed.cmd[2]);
	return (OK);
}
