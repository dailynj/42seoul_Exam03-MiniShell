#include "builtin.h"

int m_env()
{
	inorder(environ, tree());
	return (1); // 수정
}
