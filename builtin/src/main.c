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



void	sigint_handler(int errno)
{
	(void)errno;
	if (g_pid > 0)
	{
		printf("\n");
	}
	// else
	// {
	// 	printf("\b\b  \b\b\n");
	// 	print_pwd(LONG);
	// }
}


int		main(int ac, char **av, char **env)
{
	t_term term;
	t_dummy history;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	init_tree(env);
	init_term(&term);
	init_list(&history);
	init_list(&env_list);
	while (*env)
	{
		add_list_sort(&env_list, *env);
		++env;
	}
	// print_list(&env_list);
	start_shell(&term, &history);
	free_tree();
	free_list(&env_list);
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
	while (read(0, &ch, sizeof(ch)) > 0)
	{
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
			g_errno = 126;
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
			g_question = "0";
			break ;
		}
		else
		{
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
	char		**temp;
	int			i;

	g_read_buf = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		g_errno = 0;
		print_pwd(LONG);
		noncanonical_input(g_read_buf, term, history);
		if (g_errno)
			continue ;
		if (check_syntax(g_read_buf) || check_pipe(g_read_buf)) //|| check_redirection(g_read_buf))
		{
			printf("bash: Syntax error\n");
			continue ;
		}
		replace_env(g_read_buf);
		pipe_str = m_split_char(g_read_buf, REAL_PIPE);
		temp = pipe_str;

		i = -1;
		int pipe_len = m_arrsize(pipe_str);
		int final = 0;
		int fds = 0;
		while (++i < pipe_len)
		{
			t_dummy		std_in; // < <<
			t_dummy		std_out; // > >>
			init_list(&std_out);
			init_list(&std_in);


			if (i == pipe_len - 1)
				final = 1;
			else
			{
				fds = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
				close(fds);
				add_list(std_in.tail, "a.txt", 0);
			}
			m_memset(&parsed, 0, sizeof(t_parsed));
			parsed = get_cmd(*pipe_str);
			char *tmp;

			fill_list(parsed.cmd[2], '<', &std_in);
			fill_list(parsed.cmd[2], '>', &std_out);
			tmp = core_cmd(parsed.cmd[2]);
			m_memset(parsed.cmd[2], 0, BUFFER_SIZE);
			m_strlcpy(parsed.cmd[2], tmp, m_strlen(tmp) + 1);
			free(tmp);

			int in_fds;
			int out_fds;
			in_fds = redi_stdin(std_in.head->right);
			out_fds = redi_stdout(std_out.head->right);
			if (in_fds == -1)
				continue ;
			// 만약 error면 break ;
			g_question = "0";
			if (m_strlen(parsed.cmd[0]) == 0)
			{
				++pipe_str;
				continue ;
			}
			tmp = join_parsed(parsed);
			if (!run_builtin(parsed, &std_out))
			{
				run_execved(tmp, parsed, in_fds, out_fds, &std_in, &std_out);
			}
			free(tmp);
			tmp = 0;
			++pipe_str;
		}
		m_free_split(temp);
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
