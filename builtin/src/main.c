#include "builtin.h"

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;

	// char *str;
	// t_tree *tmp;

	// tmp = malloc(sizeof(t_tree));
	// printf("addr : %p\n", tmp);
	// m_strcpy(tmp->val, "hello");
	// printf("str : %s\n", tmp->val);

	// free(tmp);
	// t_tree *tmp2 = malloc(sizeof(t_tree));
	// printf("addr : %p\n", tmp);
	// printf("str : %s\n", tmp->val);

	// /*
	// write(1, "here!\n", 6);
	init_tree(env);
	// insert_tree("kr=ks");
	// insert_tree("hB=ks");
	// insert_tree("i=asdf");
	// insert_tree("d=ks");
	// insert_tree("cL=asdf");
	// insert_tree("f=pqwer");
	// insert_tree("bcde=bcde");
	// insert_tree("e=asdf");
	// insert_tree("or=ks");
	// insert_tree("j=pqwer");
	// insert_tree("lB=ks");
	// insert_tree("pB=ks");
	// insert_tree("gr=ks");
	// insert_tree("n=pqwer");
	// insert_tree("m=asdf");
	// inorder_print(tree(), export);
	// printf("------------------------\n");
	// delete_tree("i");
	// delete_tree("j");
	// inorder_print(tree(), export);
	// printf("------------------------\n");
	start_shell();
	return (0);
}

// int copy_size(char *env)
// {
// 	int idx;

// 	idx = 0;
// 	if (env[idx] != '$')
// 		return (0);
// 	while (env[idx] !=)
// 		++idx;
// 	return (idx);
// }



int start_shell()
{
	// char *short_pwd;
	char	read_buf[BUFFER_SIZE];
	int		read_size;
	char	**pipe_str;
	char	**temp;
	t_parsed parsed;

	while (1)
	{
		print_pwd(LONG); // sunashell crab
		m_memset(read_buf, 0 , BUFFER_SIZE);
		read_size = read(0, read_buf, BUFFER_SIZE);
		read_buf[read_size - 1] = 0;
		replace_env(read_buf);

		pipe_str = m_split_char(read_buf, REAL_PIPE);
		temp = pipe_str;
		while (*pipe_str)
		{
			parsed = get_cmd(*pipe_str);
			// print_parsed(parsed);
			// pipe -> fd[0] fd[1]
			// if (m_strchr(read_buf, '<') || m_strchr(read_buf, '>'))
			// {
			// 	run_redirect(read_buf);
			// }
			if ((!run_builtin(parsed, read_size)) || (!run_execved(*pipe_str, parsed)))
			{
				printf("not command!\n");
			}
			m_memset(&parsed, 0 , sizeof(t_parsed));
			++pipe_str;
		}
		m_free_split(temp, m_arrsize(temp));
	}
	return (0);
}


//t_bool
int		run_builtin(t_parsed parsed, int read_size)
{
	if (!m_strncmp(parsed.cmd[0], "echo", read_size -1))
	{
		m_echo(parsed);
	}
	else if (!m_strncmp(parsed.cmd[0], "pwd", read_size - 1))
	{
		m_pwd(parsed);
		// 옵션이 들어오면 invalid option..?
		// 인자가 들어오면 무시
	}
	else if (!m_strncmp(parsed.cmd[0], "cd", read_size - 1))
	{
		m_cd(parsed);
		// 파싱해서 val 보내기
	}
	else if (!m_strncmp(parsed.cmd[0], "exit", read_size - 1))
	{
		m_exit();
	}
	else if (!m_strncmp(parsed.cmd[0], "env", read_size - 1))
	{
		m_env();
		// 옵션 들어오면 error 처리
		// 옵션이 아닌 str 들어올때 error 처리
	}
	else if (!m_strncmp(parsed.cmd[0], "export", read_size - 1))
	{
		m_export();
		// 1개 들어오면 search 하기
		// 0개 들어오면 전체 출력
		// 옵션 error
		// str error 처리
	}
	else if (!m_strncmp(parsed.cmd[0], "unset", read_size - 1))
	{
		m_unset("LL");
		// 파싱해서 환경변수 이름 넣어주기
		// 옵션 error
		// str error
	}
	return (1);
}

void print_pwd(int type)
{
	char cwd[PATH_MAX];
	char *temp;
	int cnt;
	int color;
	int max;

	max = type * 99999;
	temp = cwd;
	cnt = 0;
	color = 1;
	m_memset(cwd, 0, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	printf("\033[0mSuNaSHELL🦀 ");
	while (*temp)
	{
		++cnt;
		if (*temp == '/')
		{
			cnt = 0;
			color++;
		}
		if (cnt < max)
			printf("\033[0;3%dm%c", color % 6, *temp);
		++temp;
	}
	printf("\033[0;3%dm\n", (color + 1) % 6);
	write(1, "> ", 3);
}
