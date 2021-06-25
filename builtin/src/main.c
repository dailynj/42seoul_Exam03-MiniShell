#include "builtin.h"

int g_errno;

void sigint_handler()
{
	if (g_pid > 0)
	{
		printf("\b\b  \b\b\n");
		signal(SIGINT, SIG_IGN);
	}
	else
	{
		printf("\b\b  \b\b\n");
		print_pwd(LONG);
	}
}
void sigquit_handler()
{
	// ctrl + backslash
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	init_tree(env);
	start_shell();
	return (0);
}

void reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}

void set_input_mode(void)
{
	tcgetattr(STDIN_FILENO, &org_term);
	atexit(reset_input_mode); // 빼야할 것
	
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ICANON | ECHO);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

int start_shell()
{
	char	**pipe_str;
	char	**temp;
	int		ch;
	int		i;
	// int		*fds;
	t_parsed parsed;

	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigquit_handler);
	set_input_mode();
	while (1)
	{
		i = -1;
		print_pwd(LONG); // sunashell crab
		m_memset(g_read_buf, 0, BUFFER_SIZE);
		while (read(0, &ch, 1) > 0)
		{
			write(0, &ch, sizeof(int));
			if (ch == 4)
				continue ;
			else if (ch == 127)
			{
				write(0, "\b \b", 3);
				g_read_buf[i--] = 0;
			}
			else if (ch == '\n')
			{
				g_read_buf[++i] = 0;
				break;
			}
			else
				g_read_buf[++i] = ch;
		}
		if (check_syntax())
		{
			printf("bash: Syntax error\n");
			continue;
		}
		replace_env();
		pipe_str = m_split_char(g_read_buf, REAL_PIPE);
		temp = pipe_str;
		// fds = malloc(sizeof(int) * m_arrsize(pipe_str));
		// int fdx = -1;
		// if (!fds)
		// 	return (0);
		while (*pipe_str)
		{
			// open(fds[++fdx], );
			m_memset(&parsed, 0, sizeof(t_parsed));
			parsed = get_cmd(*pipe_str);
			// print_parsed(parsed);
			// pipe -> fd[0] fd[1]
			// if (m_strchr(g_read_buf, '<') || m_strchr(g_read_buf, '>'))
			// {
			// 	run_redirect(g_read_buf);
			// }
			if (!run_builtin(parsed))
				run_execved(*pipe_str, parsed);
			++pipe_str;
			// close(fds[fdx]);
		}
		m_free_split(temp);
	}
	return (0);
}


//t_bool
int		run_builtin(t_parsed parsed)
{
	char cmd[BUFFER_SIZE];
	int i;

	i = -1;
	m_memset(&cmd, 0, BUFFER_SIZE);
	while (parsed.cmd[0][++i])
	{
		cmd[i] = (parsed.cmd[0][i] >= 65 && parsed.cmd[0][i] <= 90) ? parsed.cmd[0][i] + 32 : parsed.cmd[0][i];
	}
	if (!m_strncmp(cmd, "echo", 5))
	{
		return (m_echo(parsed));
	}
	else if (!m_strncmp(cmd, "pwd", 4))
	{
		return (m_pwd(parsed));
		// 옵션이 들어오면 invalid option..?
		// 인자가 들어오면 무시
	}
	else if (!m_strncmp(cmd, "cd", 3))
	{
		return (m_cd(parsed));
		// 파싱해서 val 보내기
	}
	else if (!m_strncmp(cmd, "exit", 5))
	{
		return (m_exit(parsed));
	}
	else if (!m_strncmp(cmd, "env", 4))
	{
		return (m_env(parsed));
		// 옵션 들어오면 error 처리
		// 옵션이 아닌 str 들어올때 error 처리
	}
	else if (!m_strncmp(cmd, "export", 7))
	{
		return (m_export(parsed));
		// 1개 들어오면 search 하기
		// 0개 들어오면 전체 출력
		// 옵션 error
		// str error 처리
	}
	else if (!m_strncmp(cmd, "unset", 6))
	{
		return (m_unset(parsed));
		// 파싱해서 환경변수 이름 넣어주기
		// 옵션 error
		// str error
	}
	return (0);
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
	write(1, " > ", 3);
}
