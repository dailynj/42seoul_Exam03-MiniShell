#include "builtin.h"

void	sigint_handler(int err)
{
	(void)err;
}

void	sigquit_handler(int err)
{
	(void)err;
	printf("\n");
}
