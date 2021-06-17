#include "builtin.h"


int m_exit()
{
	// 전부 다 free 해주기
	printf("exit\n");
	exit(0);
}
