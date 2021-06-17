#include "builtin.h"

int m_env()
{
	inorder_print(tree(), environ);
	return (1); // 수정
}
