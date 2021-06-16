#include "builtin.h"

int cd(char **option, char *value)
{
	int result;

	result = chdir(value);
	if (result != 0)
		return (1);
	return (0);
}
