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

int	main(int ac, char **av, char **env)
{
	t_term		term;
	t_dummy		history;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init_term(&term);
	init_list(&history);
	init_list(&g_env_list);
	while (*env)
	{
		add_list_sort(&g_env_list, *env);
		++env;
	}
	start_shell(&term, &history);
	// free_list(&g_env_list);
	return (0);
}

void	start_shell(t_term *term, t_dummy *history)
{
	char		*read_buf;
	char		**pipe_str;
	int			before_errno;
	t_idx		*itdx;

	read_buf = malloc(BUFFER_SIZE + 1);
	itdx = malloc(sizeof(t_idx));
	while (print_pwd(LONG))
	{
		itdx->i = -1;
		itdx->j = -1;
		before_errno = errno;
		errno = 0;
		noncanonical_input(read_buf, term, history);
		if (check_syntax(read_buf) || check_pipe(read_buf)
			|| check_redi(read_buf) || errno)
			continue ;
		replace_env(read_buf, before_errno, itdx);
		pipe_str = m_split_char(read_buf, REAL_PIPE);
		start_command(pipe_str);
		m_free_split(pipe_str);
		pipe_str = 0;
	}
	free(read_buf);
	read_buf = 0;
}

int	run_builtin(t_parsed *parsed, t_dummy *std_out)
{
	char	cmd[BUFFER_SIZE];
	int		i;

	i = -1;
	m_memset(&cmd, 0, BUFFER_SIZE);
	while (parsed->cmd[0][++i])
		cmd[i] = m_tolower(parsed->cmd[0][i]);
	if (!m_strncmp(cmd, "echo", 5))
		return (m_echo(parsed, std_out));
	else if (!m_strncmp(cmd, "pwd", 4))
		return (m_pwd(parsed, std_out));
	else if (!m_strncmp(cmd, "cd", 3))
		return (m_cd(parsed));
	else if (!m_strncmp(cmd, "exit", 5))
		return (m_exit(parsed));
	else if (!m_strncmp(cmd, "env", 4))
		return (m_env(parsed, std_out));
	else if (!m_strncmp(cmd, "export", 7))
		return (m_export(parsed, std_out));
	else if (!m_strncmp(cmd, "unset", 6))
		return (m_unset(parsed));
	return (0);
}

int	print_pwd(int type)
{
	char	cwd[PATH_MAX];
	char	*temp;
	int		cnt;
	int		color;

	temp = cwd;
	cnt = 0;
	color = 1;
	m_memset(cwd, 0, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (FALSE);
	printf("\033[0mSuNaSHELL🦀 ");
	while (*temp)
	{
		++cnt;
		if (*temp == '/')
		{
			cnt = 0;
			color = (color + 1) % 6 + 48;
		}
		if (cnt < BUFFER_SIZE * type)
			printf("\033[0;3%dm%c", color % 6, *temp);
		++temp;
	}
	printf("\033[0;37m\n");
	write(1, " > ", 3);
	return (TRUE);
}
