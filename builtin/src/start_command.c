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

void	child_command(t_parsed *parsed, t_std *std, int pipe_in, int pipe_len)
{
	char	*tmp;

	if (pipe_len != 1)
		close(pipe_in);
	fill_list(parsed->cmd[2], '<', std->in);
	fill_list(parsed->cmd[2], '>', std->out);
	tmp = core_cmd(parsed->cmd[2]);
	m_memset(parsed->cmd[2], 0, BUFFER_SIZE);
	m_strlcpy(parsed->cmd[2], tmp, m_strlen(tmp) + 1);
	free(tmp);
	tmp = 0;
	redi_stdout(std->out->head->right);
	tmp = join_parsed(parsed);
	if (redi_stdin(std->in->head->right) != -1
		&& !run_builtin(parsed, std->out))
		run_execved(tmp, parsed, std->in, std->out);
	free(tmp);
	tmp = 0;
	if (pipe_len != 1)
		exit(0);
}

void	parent_command(pid_t child_pid, int *status, int pipe_out)
{
	close(pipe_out);
	waitpid(child_pid, status, 0);
}

int	run_command2(t_std *std, t_parsed *parsed, t_idx ipdx, int pipe_in)
{
	int			child_pid;
	int			pipes[2];
	int			status;

	if (ipdx.j != 1)
		pipe(pipes);
	if (ipdx.i != 0)
		add_list(std->in->tail, "", pipe_in);
	if (ipdx.i != ipdx.j - 1)
		add_list(std->out->tail, "", pipes[1]);
	if (ipdx.j != 1)
		child_pid = fork();
	if (ipdx.j == 1 || child_pid == 0)
		child_command(parsed, std, pipes[0], ipdx.j);
	else
		parent_command(child_pid, &status, pipes[1]);
	return (pipes[0]);
}

int	run_command(int idx, int *pdx, char **pipe_str, int pipe_in)
{
	t_parsed	*parsed;
	t_idx		ipdx;
	t_std		std;

	ipdx.i = idx;
	ipdx.j = m_arrsize(pipe_str);
	std.in = malloc(sizeof(t_dummy));
	std.out = malloc(sizeof(t_dummy));
	init_list(std.out);
	init_list(std.in);
	parsed = get_cmd(pipe_str[++*pdx]);
	ipdx.j = run_command2(&std, parsed, ipdx, pipe_in);
	free_list(&std.out);
	free_list(&std.in);
	free(parsed);
	parsed = 0;
	return (ipdx.j);
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
