#include "builtin.h"

int	m_cd(t_parsed parsed)
{
	int result;

	result = chdir(parsed.cmd[2]);
	if (result != 0)
		return (1);
	return (0);
}
