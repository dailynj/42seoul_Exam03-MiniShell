#include "builtin.h"

int m_export()
{
	inorder_print(tree(), export);
	return (OK); //	수정
}
