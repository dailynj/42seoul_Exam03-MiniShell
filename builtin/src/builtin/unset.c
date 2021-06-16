#include "builtin.h"

int m_unset(char *val)
{
	delete_tree(val);
	return (0);
}
