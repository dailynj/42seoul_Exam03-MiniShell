#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void (*old_fun)(int);

void sigint_handler(int signo)
{
	printf("signo : %d", signo);
   printf("Ctrl-C 키를 눌루셨죠!!\n");
   printf("또 누르시면 종료됩니다.\n");
   signal(SIGINT, old_fun);
   //signal( SIGINT, SIG_DFL);
}

int main( void)
{
   old_fun = signal(SIGINT | SIGQUIT, sigint_handler);
   // printf("asdf : %d", SIGTSTP);
   // printf("zxcv : %d", SIGCHLD);
   while (1)
   {
      printf("forum.falinux.com\n");
      sleep(1);
   }
}