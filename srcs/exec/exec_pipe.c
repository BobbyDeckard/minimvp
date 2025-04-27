/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:22:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/27 17:22:46 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	close_redirs(t_ast *ast, t_cmd cmd)
{
	int	type;
	int	i;

	i = -1;
	if (ast->children)
	{
		while (ast->children[++i])
		{
			type = ast->children[i]->type;
			if (type == NODE_REDIR_IN)
				close(cmd.fd_in);
			else if (type == NODE_REDIR_OUT || type == NODE_REDIR_APPEND)
				close(cmd.fd_out);
		}
	}
}

void	dup_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2: fd_in");
			exit(1);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2: fd_out");
			exit(1);
		}
		close(cmd->fd_out);
	}
}

int	run_pipe(t_ast **children, char **paths, char **envp, int *pids, int count)
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
			make_redirs(children[i], &children[i]->cmd);
			dup_fds(&children[i]->cmd);
			exec_cmd(children[i]->cmd, paths, envp);	// will need to be modified for and/or nodes inside pipes
		}
		close_pipes(fd, i, count);
	}
	return (waitpids(pids, count));
}

int	exec_pipe(t_ast **children, char **paths, char **envp)
{
	int	*pids;
	int	status;
	int	count;

	count = count_commands(children);
	pids = (int *) malloc(count * sizeof(int));
	status = run_pipe(children, paths, envp, pids, count);
	free(pids);
	return (status);
}
