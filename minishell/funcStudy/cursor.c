// #include <stdio.h>
// #include <stdlib.h>

// #include <termcap.h>
// #include <termios.h>
// #include <unistd.h>

// #define BACKSPACE 127
// #define LEFT_ARROW 4479771
// #define RIGHT_ARROW 4414235

// struct termios	new_term;

// void	set_terminal(void)
// {
// 	tcgetattr(STDIN_FILENO, &new_term);
// 	new_term.c_lflag &= ~(ICANON | ECHO);
// 	new_term.c_cc[VMIN] = 1;
// 	new_term.c_cc[VTIME] = 0;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
// }

// int main(void)
// {
// 	tgetent(NULL, "xterm");
// 	char *cm = tgetstr("cm", NULL); //cursor motion
// 	char *ce = tgetstr("ce", NULL); //clear line from cursor

// 	return (0);
// }


#include <unistd.h>
#include <termcap.h>

int putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int main(void)
{
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, 0, 0), 1, putchar_tc);
}
