#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
     
    pid_t pid;
    int status,i;
     
    pid = fork();

	if (pid > 0)
	{
		pid_t waitpid;
		printf("부모 PID : %d, 자식 PID : %d\n", getpid(), pid);
	}
		else if(pid == 0){  // 자식 프로세스
		for (int i = 0 ; i < 3 ; ++i)
			sleep(1);
        printf("자식 PID : %ld \n",(long)getpid());
        printf("자식 종료\n");
	}
    else {  // fork 실패
        perror("fork Fail! \n");
        return -1;
    }
     
	pid  = waitpid(pid, &status, 0);
    if (pid == -1 )
	{
		printf("error\n");
	}
	else
	{
		if (WIFEXITED(status)){
			printf("프로그램에서 exited(%d) 또는 main에서 return ;하여 종료되었습니다.\n",
					WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("siganl %d번이 발생하여 종료되었습니다.\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("signal %d번으로 인하여 stop되었습니다. \n", WSTOPSIG(status));
		} else if (WIFCONTINUED(status)) {
			printf("stop된 프로세스를 진행합니다\n");
		}
	}
     
    return 0;
}
