#include "builtin.h"

// fork 해서 자식 프로세스가 실행하도록
int run_execved(char *pipe_str, t_parsed parsed)
{
	char **exec_str;
	char **envp;
	char **path_arr;
	char **tmp_path_arr;
	// pid_t pid;
	// char *path;
	(void) parsed;
		
	envp = malloc(tree()->size + 1);
	inorder_execve(tree(), &envp, 0); // sunashell 의 환경변수 목록 넘기는 함수
	int temp = 0;
	
	printf("tree size : %d\n",tree()->size + 1);
	while (envp[temp])
	{
		printf("[envp[%d] : %s]\n", temp, envp[temp]);
		++temp;
	}
	// inorder_print(tree(), export);
	exec_str = m_split_char(pipe_str, ' ');
	path_arr = m_split_char(m_find_env("PATH"), 58);
	tmp_path_arr = path_arr;

	// 1. pipe_str split -> white space
	// 2. 마지막에 null
	// ㄴ fork해서 실행
	// 3. exec_str free 해주기!
	/*
	pid = fork();
	if (pid == 0)
	{
		int idx = 0;
		printf("-> path_arr[4], %s\n", tmp_path_arr[4]);
		
		printf("-> inorder 밑, %s\n\n\n\n\n", tmp_path_arr[4]);
		while (tmp_path_arr[idx])
		{
			printf("-> path_arr[4], %s\n", tmp_path_arr[4]);
			printf("----> path_arr[%d], %s\n", idx, tmp_path_arr[idx]);
			// printf("tmp_path : %s\n", tmp_path_arr[idx]);
			path = m_strjoin(tmp_path_arr[idx], m_strjoin("/", parsed.cmd[0]));
			// printf("path : %s\n", path);
			execve(path, exec_str, envp);
			free(path);
			++idx;
		}
		// 만약 와일문을 탈출했으면 에러처리 해야함
		// 여기서 return 말고 exit으로 처리해야함
		return (0);
	}
	*/
	// waitpid()
	// 자식이 끝날 때 까지 기다렸다가 만약 자식이 error상태로 끝나면 return 에러
	m_free_split(path_arr, m_arrsize(path_arr));
	m_free_split(exec_str, m_arrsize(exec_str));
	
	return (1);
}