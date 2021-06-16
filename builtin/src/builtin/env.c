#include "builtin.h"

int m_env()
{
	inorder(environ, tree());
}
