/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:22:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/08 13:23:31 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	waitpids(int *pids, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		waitpid(pids[i], NULL, 0);
}

int	count_commands(t_ast **children)
{
	int	i;

	i = 0;
	while (children[i])
		i++;
	return (i);
}

int	make_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	make_pipes(int fd[2][2])
{
	if (pipe(fd[0]) == -1)
	{
		perror("pipe");
		exit (1);
	}
	if (pipe(fd[1]) == -1)
	{
		perror("pipe");
		close(fd[0][0]);
		close(fd[0][1]);
		exit(1);
	}
}

void	set_fds(t_ast *cmd1, t_ast *cmd2, int fd[2])
{
	if (cmd1)
		cmd1->cmd.fd_out = fd[1];
	if (cmd2)
		cmd2->cmd.fd_in = fd[0];
}

void	close_pipes(int fd[2][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}

void	dup_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	/*
	ft_putstr_fd("fd macroes: ", 2);
	ft_putnbr_fd(STDIN_FILENO, 2);
	ft_putchar_fd(' ', 2);
	ft_putnbr_fd(STDOUT_FILENO, 2);
	ft_putchar_fd('\n', 2);
	*/
}

void	make_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

int	exec_pipe_cmd(t_cmd cmd, char **paths, char **envp)
{
	get_cmd_path(&cmd, paths);
	if (!cmd.path)
		return (FAILURE);
	if (!execve(cmd.path, cmd.args, envp))
		return (FAILURE);
	ft_putstr_fd("wtf\n", 2);
	return (SUCCESS);
}

void	run_pipe(t_ast **children, char **paths, char **envp, int *pids, int count)
{
	int	fd[2][2];
	int	i;

	make_pipes(fd);
	i = -1;
	while (++i < count)
	{
		if (i + 1 < count)
			set_fds(children[i], children[i + 1], fd[i % 2]);
		pids[i] = make_fork();
		if (pids[i] == 0)
		{
			dup_fds(&children[i]->cmd);
			close_pipes(fd);
			if ((children[i])->type == NODE_CMD)
				exec_pipe_cmd((children[i])->cmd, paths, envp);
			else if (children[i])
				exec_ast(children[i], paths, envp);
		}
	}
	close_pipes(fd);
	waitpids(pids, count);
}

int	exec_pipe(t_ast **children, char **paths, char **envp)
{
	int	*pids;
	int	count;

	count = count_commands(children);
	pids = (int *) malloc(count * sizeof(int));
	run_pipe(children, paths, envp, pids, count);
	free(pids);
	return (SUCCESS);
}
