#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

int main(int argc, char *argv[])
{
	char	**new_argv;
	char	command[] = "ls";
	int		idx;

	new_argv = malloc(sizeof(char *) * argc + 1);
	// 명령어를 ls로 변경
	new_argv[0] = command;

	// command line으로 넘어온 parameter를 그대로 사용
	for (idx = 1 ; idx < argc ; ++idx)
		new_argv[idx] = argv[idx];

	// argc를 execve 파라미터에 전달할 수 없기 때문에 NULL을 끝으로 지정해우저야 함
	new_argv[argc] = NULL;

	if (execve("/bin/ls", new_argv, environ) == -1){
		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
		return 1;
	}
	printf("이후 로직은 실행되지 않습니다..\n");
	return (0);
}
