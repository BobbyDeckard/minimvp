/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:19:35 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 15:31:00 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

t_pip	init_pip(t_cmd *cmd1, t_cmd *cmd2)
{
	t_pip	pip;

	if (pipe(pip.fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pip.cmd1_args = cmd1->args;
	pip.cmd1_path = cmd1->path;
	pip.fdin = cmd1->fdin;
	pip.cmd2_args = cmd2->args;
	pip.cmd2_path = cmd2->path;
	pip.fdout = cmd2->fdout;
	return (pip);
}

static int	make_fork(t_pip *pip, char *path)
{
	int	pid;
	
	pid = 1;
	if (path)
		pid = fork();
	if (pid < 0)
	{
		perror("fork");
		clean_exit_pipe(pip);
	}
	return (pid);
}

static void	exec_cmd1(t_pip *pip, char **envp)
{
	dup2(pip->fdin, STDIN_FILENO);
	dup2(pip->fd[1], STDOUT_FILENO);
	close_fds(pip);
	if (!pip->cmd1_path)
		clean_exit_pipe(pip);
	if (!execve(pip->cmd1_path, pip->cmd1_args, envp))
	{
		perror("execve");
		clean_exit_pipe(pip);
	}
}

static void	exec_cmd2(t_pip *pip, char **envp)
{
	dup2(pip->fd[0], STDIN_FILENO);
	dup2(pip->fdout, STDOUT_FILENO);
	close_fds(pip);
	if (!pip->cmd2_path)
		clean_exit_pipe(pip);
	if (!execve(pip->cmd2_path, pip->cmd2_args, envp))
	{
		perror("execve");
		clean_exit_pipe(pip);
	}
}

static void	exec_pipe(t_pip *pip, char **envp)
{
	int	pid1;
	int	pid2;

	pid1 = make_fork(pip, pip->cmd1_path);
	if (pid1 == 0)
		exec_cmd1(pip, envp);
	pid2 = make_fork(pip, pip->cmd2_path);
	if (pid2 == 0)
		exec_cmd2(pip, envp);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	pipex(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	t_pip	pip;

	pip = init_pip(cmd1, cmd2);
	exec_pipe(&pip, envp);
	clean_up_pipe(&pip);
}
