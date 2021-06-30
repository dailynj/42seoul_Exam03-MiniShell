#include "builtin.h"

void init_term(t_term *term)
{
	tcgetattr(STDIN_FILENO, &term->org_term);
	tcgetattr(STDIN_FILENO, &term->new_term);
	term->new_term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term->new_term.c_cc[VMIN] = 1;
	term->new_term.c_cc[VTIME] = 0;
}

void reset_input_mode(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->org_term);
}


void set_input_mode(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
}
