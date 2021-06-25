#include "builtin.h"

// fork 해서 자식 프로세스가 실행하도록
int run_execved(char *pipe_str, t_parsed parsed)
{
	char **exec_str;
	char **tmp_exec_str;
	char **envp;
	char **path_arr;
	char **tmp_path_arr;
	char *path;
	
	int status;

	if (g_fds == 1)
		exec_str = m_split_char(pipe_str, ' ');
	else
	{
		int idx = 0;
		m_memset(&g_read_buf, 0, BUFFER_SIZE);
		read(g_fds, &g_read_buf, BUFFER_SIZE);
		tmp_exec_str = m_split_char(g_read_buf, ' ');
		exec_str = malloc(sizeof(char *) * (m_arrsize(tmp_exec_str) + 2));
		exec_str[idx] = m_strdup(parsed.cmd[0]);
		while(exec_str[++idx])
		{
			exec_str[idx] = m_strdup(tmp_exec_str[idx - 1]);
		}
		exec_str[idx] = 0;
	}
	path_arr = m_split_char(m_find_env("PATH"), 58);
	if (!path_arr)
	{
		printf("Error: not found\n");
		return (0); // error 처리
	}
	tmp_path_arr = path_arr;
	envp = malloc(sizeof(char *) * tree()->size + 1);
	inorder_execve(tree(), &envp, 0); // sunashell 의 환경변수 목록 넘기는 함수
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(g_fds, 1);
		int idx = 0;
		while (tmp_path_arr[idx])
		{
			path = m_strjoin(tmp_path_arr[idx], m_strjoin("/", parsed.cmd[0]));
			// printf("path : %s\n", path);
			execve(path, exec_str, envp); // 에러처리 필요
			free(path);
			++idx;
		}
		// 만약 와일문을 탈출했으면 에러처리 해야함
		// 여기서 return 말고 exit으로 처리해야함
		if (parsed.cmd[0][0] == '/')
		{
			printf("%s: No such file or directory\n", parsed.cmd[0]);	
		}
		else 
		{
			printf("%s: command not found!\n", parsed.cmd[0]);
		}
		exit(0);
	}
	else
	{
		wait(&status);
		// 자식이 끝날 때 까지 기다렸다가 만약 자식이 error상태로 끝나면 return 에러
		if (g_fds == 1)
			m_free_split(exec_str);
		m_free_split(path_arr);
		g_pid = 0;
		return (1);
	}
}
