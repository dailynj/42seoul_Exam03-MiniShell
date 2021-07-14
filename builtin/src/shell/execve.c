/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:54 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:03:56 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	find_path(t_parsed *parsed, t_execve *exec)
{
	int		idx;
	char	*temp;
	char	*path;

	idx = 0;
	while (exec->path_arr[idx])
	{
		temp = m_strjoin("/", parsed->cmd[0]);
		path = m_strjoin(exec->path_arr[idx], temp);
		free(temp);
		execve(path, exec->exec_str, exec->envp);
		free(path);
		++idx;
	}
}

void	run_execve_child_noslash(t_dummy *std_in, t_dummy *std_out)
{
	int		ifd;
	int		ofd;

	if (m_strlen(std_out->tail->left->val) == 0
		&& std_out->tail->left->db != -1)
		ofd = std_out->tail->left->db;
	else if (std_out->tail->left->db == 1)
		ofd = open(std_out->tail->left->val, O_WRONLY | O_APPEND, 0777);
	else
		ofd = open(std_out->tail->left->val, O_WRONLY | O_TRUNC, 0777);
	if (std_in->tail->left->db == 1)
		ifd = open("stdout", O_RDONLY);
	else
		ifd = open(std_in->tail->left->val, O_RDONLY);
	dup2(ifd, STDIN_FILENO);
	dup2(ofd, STDOUT_FILENO);
	close(ofd);
	close(ifd);
}

void	run_execve_child(t_execve *exec, t_parsed *parsed,
	t_dummy *std_in, t_dummy *std_out)
{
	if (m_strchr(parsed->cmd[0], '/'))
		execve(parsed->cmd[0], exec->exec_str, exec->envp);
	else
	{
		run_execve_child_noslash(std_in, std_out);
		find_path(parsed, exec);
	}
	if (m_strchr(parsed->cmd[0], '/'))
		exit(259);
	else
		exit(127);
}

int	run_execve_parent(t_execve **exec, t_parsed *parsed, int status)
{
	wait(&status);
	errno = status >> 8;
	if (errno == 0 && (status & 255))
	{
		errno = (status & 255) + 128;
		printf("\n");
	}
	if (status >> 8 == 127 && parsed->cmd[0][0] != '\0')
		printf("minishell: %s: command not found!\n", parsed->cmd[0]);
	else if (status == 768)
		printf("minishell: %s: No such file or directory\n", parsed->cmd[0]);
	m_free_split((*exec)->envp);
	m_free_split((*exec)->exec_str);
	m_free_split((*exec)->path_arr);
	free(*exec);
	return (1);
}

int	run_execved(char *pipe_str, t_parsed *parsed,
		t_dummy *std_in, t_dummy *std_out)
{
	t_execve	*exec;
	int			status;
	char		*find_env;
	pid_t		child_pid;

	status = 0;
	exec = malloc(sizeof(t_execve));
	m_memset(exec, 0, sizeof(t_execve));
	exec->exec_str = m_split_char(pipe_str, ' ');
	find_env = m_find_env_list(g_env_list, "PATH");
	exec->path_arr = m_split_char(find_env, 58);
	if (!exec->path_arr && !m_strchr(parsed->cmd[0], '/'))
	{
		printf("minishell: %s: command not found\n", parsed->cmd[0]);
		return (0);
	}
	free(find_env);
	exec->envp = make_envp(g_env_list);
	child_pid = fork();
	if (child_pid == 0)
		run_execve_child(exec, parsed, std_in, std_out);
	else
		return (run_execve_parent(&exec, parsed, status));
	return (1);
}
