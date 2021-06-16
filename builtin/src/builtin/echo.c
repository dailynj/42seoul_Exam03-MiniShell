#include "builtin.h"

int echo(char **option, char* value)
{
	printf("\\%s", value);

	if (option != 0 && option[0][0] != 'n')
		return (0);
	printf("\n");
	return (0);
}
