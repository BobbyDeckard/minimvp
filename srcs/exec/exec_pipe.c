/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:22:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/09 12:58:56 by imeulema         ###   ########.fr       */
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

void	close_pipes(int fd[2][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}

void	overcomplicated_close_pipes(int fd[2][2], int count, int i)
{
	if (i + 3 == count)
		close(fd[(count + 1) % 2][1]);	// closing the penultimate pipe's write end
										// when executing the 3rd to last cmd
	else if (i + 2 == count)
	{
		close(fd[(count + 1) % 2][0]);	// closing the penultimate pipe's read end
		close(fd[count % 2][1]);		// closing the last pipe's write end when
										// executing the 2nd to last cmd
	}
	else if (i + 1 == count)
		close(fd[count % 2][0]);		// closing the last pipe's read end when
										// executing the last cmd
}

void	dup_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
}

void	set_fds(t_ast *cmd1, t_ast *cmd2, int fd[2])
{
	if (cmd1)
		cmd1->cmd.fd_out = fd[1];
	if (cmd2)
		cmd2->cmd.fd_in = fd[0];
}

int	make_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	return (1);
}

int	exec_pipe_cmd(t_cmd cmd, char **paths, char **envp)
{
	get_cmd_path(&cmd, paths);
	if (!cmd.path)
		return (FAILURE);
	if (execve(cmd.path, cmd.args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
	return (SUCCESS);
}

void	run_pipe(t_ast **children, char **paths, char **envp, int *pids, int count)
{
	int	fd[2][2];
	int	i;

	i = -1;
	while (++i < count)
	{
		if (i + 1 < count && make_pipe(fd[i % 2]))
		{
			children[i]->cmd.fd_out = fd[i % 2][1];
			children[i + 1]->cmd.fd_in = fd[i % 2][0];
		}
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
		if (i != 0)
			close(fd[(i + 1) % 2][0]);
		if (i + 1 < count)
			close(fd[i % 2][1]);
	}
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
