/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:22:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 13:22:06 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	*init_pids(int count)
{
	int	*pids;
	int	i;

	pids = (int *) malloc(count * sizeof(int));
	if (!pids)
	{
		perror("malloc");
		return (NULL);
	}
	i = -1;
	while (++i < count)
		pids[i] = -1;
	return (pids);
}

void	link_pipe(t_ast *cmd1, t_ast *cmd2, int fd[2][2], int i)
{
	int	j;

	if (cmd1->type == NODE_CMD)
		cmd1->cmd.fd_out = fd[i % 2][1];
	else
	{
		j = -1;
		while (cmd1->children[++j])
			cmd1->children[j]->cmd.fd_out = fd[i % 2][1];
	}
	if (cmd2->type == NODE_CMD)
		cmd2->cmd.fd_in = fd[i % 2][0];
	else
	{
		j = -1;
		while (cmd2->children[++j])
			cmd2->children[j]->cmd.fd_in = fd[i % 2][0];
	}
}

void	exec_pipe_cmd(t_ast *cmd)
{
	if (make_redirs(cmd, &cmd->cmd) == FAILURE)
		clean_exit(cmd->root, FAILURE);
	dup_fds(*cmd);
	exec_cmd(cmd, cmd->cmd);
	clean_exit(cmd->root, FAILURE);
}

void	exec_pipe_and(t_ast *and)
{
	int	status;
	int	pid;
	int	i;

	i = -1;
	while (and->children[++i])
	{
		if (and->children[i]->type == NODE_CMD)
		{
			pid = make_fork();
			if (pid == 0)
				exec_pipe_cmd(and->children[i]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			if (status != SUCCESS)
				break;
		}
		else
			exec_pipe_child(and->children[i]);
	}
}

void	exec_pipe_or(t_ast *or)
{
	int	status;
	int	pid;
	int	i;

	i = -1;
	while (or->children[++i])
	{
		pid = make_fork();
		if (pid == 0)
			exec_pipe_child(or->children[i]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == SUCCESS)
			break;
	}
}

void	exec_pipe_child(t_ast *child)
{
	if (child->type == NODE_CMD)
		exec_pipe_cmd(child);
	else if (child->type == NODE_AND_IF)
		exec_pipe_and(child);
	else if (child->type == NODE_OR_IF)
		exec_pipe_or(child);
}

int	run_pipe(t_ast **children, int *pids, int count)
{
	int	fd[2][2];
	int	i;

	i = -1;
	while (++i < count)
	{
		if (i + 1 < count && make_pipe(fd[i % 2]))
		{
			if (make_pipe(fd[i % 2]))
				link_pipe(children[i], children[i + 1], fd, i);
			else
				return (pipe_error(pids, fd, i, count));
		}
		if (children[i] == NODE_CMD && is_builtin(children[i]->cmd))
		{
			pids[i] = -1;
			exec_builtin(children[i]);
		}
		else
			pids[i] = make_fork();
		if (pids[i] == 0)
			exec_pipe_child(children[i]);
		close_pipes(fd, i, count);
	}
	return (waitpids(pids, count));
}

int	exec_pipe(t_ast **children)
{
	int		*pids;
	int		status;
	int		count;

	count = count_nodes(children);
	pids = init_pids(count);
	if (!pids)
		return (FAILURE);
	status = run_pipe(children, pids, count);
	free(pids);
	return (status);
}
