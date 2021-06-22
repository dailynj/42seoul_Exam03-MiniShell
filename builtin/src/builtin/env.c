#include "builtin.h"

int m_env()
{
	inorder_print(tree(), environ);
	return (OK); // 수정
}
