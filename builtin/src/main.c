/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:48 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:48 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	sigint_handler(int err)
{
	(void)err;
	// if ()
	// printf("\n");
}

void	sigquit_handler(int err)
{
	(void)err;
	printf("\n");
}

int		main(int ac, char **av, char **env)
{
	t_term term;
	t_dummy history;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);

	init_term(&term);
	init_list(&history);
	init_list(&env_list);
	while (*env)
	{
		add_list_sort(&env_list, *env);
		++env;
	}
	start_shell(&term, &history);
	// free_list(&env_list);
	return (0);
}

void	noncanonical_input(char *g_read_buf, t_term *term, t_dummy *history)
{
	char tmp_read_buf[BUFFER_SIZE];
	int	ch;
	int	i;
	int k;
	int hdx;

	ch = 0;
	i = -1;
	hdx = 0;
	m_memset(tmp_read_buf, 0, BUFFER_SIZE);
	m_memset(g_read_buf, 0, BUFFER_SIZE);
	set_input_mode(term);
	// printf("g_read_buf : %s\n", g_read_buf);
	while (read(0, &ch, sizeof(ch)) > 0)
	{
		// printf("ch : %c             = \n", ch);
		if (ch == 4283163) // up
		{
			if (history_up(i, hdx, history, &g_read_buf))
			{
				k = -1;
				while (g_read_buf[++k])
					write(1, &g_read_buf[k], 1);
				i = k - 1;
				++hdx;
			}
		}
		else if (ch == 4348699) // down
		{
			if (hdx == 1 && history_down(i, hdx, history, &g_read_buf))
			{
				m_strlcpy(g_read_buf, tmp_read_buf, m_strlen(tmp_read_buf) + 1);
				k = -1;
				while (g_read_buf[++k])
					write(1, &g_read_buf[k], 1);
				i = k - 1;
				--hdx;
			}
			else if (hdx != 0 && history_down(i, hdx, history, &g_read_buf))
			{
				k = -1;
				while (g_read_buf[++k])
					write(1, &g_read_buf[k], 1);
				i = k - 1;
				--hdx;
			}
		}
		else if (ch == 4)
		{
			if (i == -1)
			{
				reset_input_mode(term);
				printf("exit\n");
				exit(0);
			}
			else
				continue ;
		}
		else if (ch == 3)
		{
			errno = 1;
			write(1, "\n", 1);
			break ;
		}
		else if (ch == 127)
		{
			if (i >= 0)
			{
				write(1, "\b \b", 3);
				tmp_read_buf[i] = 0;
				g_read_buf[i--] = 0;
				delete_val(hdx, history);
			}
		}
		else if (ch == '\n')
		{

			g_read_buf[++i] = 0;
			tmp_read_buf[i] = 0;
			write(1, &ch, 1);
			if (g_read_buf[0] != '\0')
				add_list(history->tail, g_read_buf, 0);
			ch = 0;
			break ;
		}
		else
		{
			// printf("in\n");
			g_read_buf[++i] = ch;
			tmp_read_buf[i] = ch;
			write_val(hdx, history, ch);
			write(1, &ch, 1);
		}
		ch = 0;
	}
	reset_input_mode(term);
}

int		start_shell(t_term *term, t_dummy *history)
{
	char		*g_read_buf;
	char		**pipe_str;
	t_parsed	parsed;
	int			i;
	int			before_errno;

	g_read_buf = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		before_errno = errno;
		errno = 0;
		print_pwd(LONG);
		noncanonical_input(g_read_buf, term, history);
		if (check_syntax(g_read_buf) || check_pipe(g_read_buf) || check_redi(g_read_buf))
		{
			printf("bash: Syntax error\n");
			continue ;
		}
		if (errno)
			continue ;
		replace_env(g_read_buf, before_errno);
		pipe_str = m_split_char(g_read_buf, REAL_PIPE);
		i = -1;
		int pipe_len = m_arrsize(pipe_str);
		int pdx = -1;
		int child_pid;
		int status;
		int dupipe = 0;
		while (++i < pipe_len)
		{
			printf("----------loop----------\n");
			t_dummy		*std_in; // < <<
			t_dummy		*std_out; // > >>
			std_in = malloc(sizeof(t_dummy));
			std_out = malloc(sizeof(t_dummy));
			init_list(std_out);
			init_list(std_in);
			if (i != 0)
			{
				dupipe = dup(pipes[0]);
				add_list(std_in->tail, "", dupipe);
				printf("print -> %d, dup : %d\n", pipes[0], dupipe);
				// char test[30];
				// read(pipes[0], &test, 30);
				// printf(" > test : %s\n", test);
			}
			print_list(std_in); // p list
			// get_cmd 안에서 memset
			m_memset(&parsed, 0, sizeof(t_parsed));
			parsed = get_cmd(pipe_str[++pdx]);


			if (pipe_len != 1)
				pipe(pipes);
			printf("[pipes : %d %d]\n", pipes[0], pipes[1]);
			if (i != pipe_len - 1)
				add_list(std_out->tail, "", pipes[1]);
			if (pipe_len != 1)
			{
				child_pid = fork();
			}

			if (pipe_len == 1 || child_pid == 0) // 자식 프로세스일때 
			{
				if (pipe_len != 1)
					close(pipes[0]); // 읽기용 파이프 닫기
				char *tmp;
				fill_list(parsed.cmd[2], '<', std_in);
				fill_list(parsed.cmd[2], '>', std_out);

				tmp = core_cmd(parsed.cmd[2]);

				m_memset(parsed.cmd[2], 0, BUFFER_SIZE);
				m_strlcpy(parsed.cmd[2], tmp, m_strlen(tmp) + 1);
				free(tmp);

				redi_stdin(std_in->head->right);
				redi_stdout(std_out->head->right);

				// 만약 error면 break ;
				if (m_strlen(parsed.cmd[0]) == 0)
				{
					++pdx;
					continue ;
				}
				tmp = join_parsed(parsed);
				print_list(std_in); // p list
				if (!run_builtin(parsed, std_out))
					run_execved(tmp, parsed, std_in, std_out);
				free(tmp);
				
				
				tmp = 0;
				if (pipe_len != 1)
				{
					// printf("go parent!\n");
					exit(0);
				}
			}
			else
			{
				// printf("wait..\n");
				waitpid(child_pid, &status, 0);
				close(pipes[1]); // 쓰기용 파이프 닫기
				// printf("done..\n");
				printf("head db %d, tail db %d\n", std_in->head->db, std_in->tail->db);
				printf("head db %d, tail db %d\n", std_out->head->db, std_out->tail->db);
				// free_list(&std_out);
				// free_list(&std_in);
				continue ;
			}
		}
		m_free_split(pipe_str);
	}
	free(g_read_buf);
	return (0);
}

// t_bool
int		run_builtin(t_parsed parsed, t_dummy *std_out)
{
	char	cmd[BUFFER_SIZE];
	int		i;

	i = -1;
	m_memset(&cmd, 0, BUFFER_SIZE);
	while (parsed.cmd[0][++i])
	{
		cmd[i] = (parsed.cmd[0][i] >= 65 && parsed.cmd[0][i] <= 90)
					 ? parsed.cmd[0][i] + 32
					 : parsed.cmd[0][i];
	}
	if (!m_strncmp(cmd, "echo", 5))
	{
		return (m_echo(parsed, std_out));
	}
	else if (!m_strncmp(cmd, "pwd", 4))
	{
		return (m_pwd(parsed, std_out));
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
		return (m_env(parsed, std_out));
		// 옵션 들어오면 error 처리
		// 옵션이 아닌 str 들어올때 error 처리
	}
	else if (!m_strncmp(cmd, "export", 7))
	{
		return (m_export(parsed, std_out));
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

void	print_pwd(int type)
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
			color = (color + 1) % 6 + 48;
		}
		if (cnt < max)
		{
			printf("\033[0;3%dm%c", color % 6, *temp);
		}
		++temp;
	}
	// printf("\033[0;3%dm\n", (color + 1) % 6);
	printf("\033[0;37m\n");
	write(1, " > ", 3);
}
