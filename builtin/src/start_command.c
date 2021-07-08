/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:40:55 by najlee            #+#    #+#             */
/*   Updated: 2021/07/08 14:40:55 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	child_command(t_parsed *parsed, t_dummy *std_in,
			t_dummy *std_out, int pipe_in, int pipe_len)
{
	char	*tmp;

	if (pipe_in != 0)
		close(pipe_in);
	fill_list(parsed->cmd[2], '<', std_in);
	fill_list(parsed->cmd[2], '>', std_out);
	tmp = core_cmd(parsed->cmd[2]);
	m_memset(parsed->cmd[2], 0, BUFFER_SIZE);
	m_strlcpy(parsed->cmd[2], tmp, m_strlen(tmp) + 1);
	free(tmp);
	tmp = 0;
	redi_stdout(std_out->head->right);
	tmp = join_parsed(parsed);
	if (redi_stdin(std_in->head->right) != -1 && !run_builtin(parsed, std_out))
		run_execved(tmp, parsed, std_in, std_out);
	free(tmp);
	tmp = 0;
	if (pipe_len != 1)
		exit(0);
}

void	parent_command(pid_t child_pid, int *status, int pipe_out)
{
	waitpid(child_pid, status, 0);
	close(pipe_out);
}

int	run_command(int idx, int *pdx, char **pipe_str, int pipe_in)
{
	int			status;
	int			child_pid;
	int			pipe_len;
	int			pipes[2];
	t_dummy		*std_in;
	t_dummy		*std_out;
	t_parsed	*parsed;

	pipe_len = m_arrsize(pipe_str);
	std_in = malloc(sizeof(t_dummy));
	std_out = malloc(sizeof(t_dummy));
	init_list(std_out);
	init_list(std_in);
	if (idx != 0)
		add_list(std_in->tail, "", pipe_in);
	parsed = get_cmd(pipe_str[++*pdx]);
	if (pipe_len != 1)
		pipe(pipes);
	if (idx != pipe_len - 1)
		add_list(std_out->tail, "", pipes[1]);
	if (pipe_len != 1)
		child_pid = fork();
	if (pipe_len == 1 || child_pid == 0)
		child_command(parsed, std_in, std_out, pipe_in, pipe_len);
	else
		parent_command(child_pid, &status, pipes[1]);
	free_list(&std_out);
	free_list(&std_in);
	free(parsed);
	parsed = 0;
	return (pipes[0]);
}

void	start_command(char **pipe_str)
{
	int	pipe_len;
	int	idx;
	int	pdx;
	int	pipe_in;

	idx = -1;
	pdx = -1;
	pipe_in = 0;
	pipe_len = m_arrsize(pipe_str);
	while (++idx < pipe_len)
	{
		pipe_in = run_command(idx, &pdx, pipe_str, pipe_in);
	}
}
