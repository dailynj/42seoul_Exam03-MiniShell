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
		waitpid = wait(&status);
		printf("부모 PID : %d, 자식 PID : %d\n", getpid(), pid);
		if (waitpid == -1)
			printf("error\n");
		else 
		{
			if (WIFEXITED(status))
				printf("자식 프로세스 정상 종료\n");
			else if (WIFSIGNALED(status))
				printf("자식 프로세스 비정상 종료: %d\n", WTERMSIG(status));
		}
	}
    else if(pid == 0){  // 자식 프로세스
		for (int i = 0 ; i < 50 ; ++i)
			sleep(1);
        printf("자식 PID : %ld \n",(long)getpid());
        printf("자식 종료\n");
	}
    else {  // fork 실패
        perror("fork Fail! \n");
        return -1;
    }
     
    return 0;
}
