/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:22:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/27 19:04:27 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	link_pipe(t_ast *cmd1, t_ast *cmd2, int fd[2][2], int i)
{
	cmd1->cmd.fd_out = fd[i % 2][1];
	cmd2->cmd.fd_in = fd[i % 2][0];
}

int	run_pipe(t_ast **children, int *pids, int count)
{
	int	fd[2][2];
	int	i;

	i = -1;
	while (++i < count)
	{
		if (i + 1 < count && make_pipe(fd[i % 2]))
			link_pipe(children[i], children[i + 1], fd, i);
		pids[i] = make_fork();
		if (pids[i] == 0)
		{
			if (children[i]->type == NODE_CMD)
			{
				make_redirs(children[i], &children[i]->cmd);
				dup_fds(*children[i]);
				exec_cmd(children[i], children[i]->cmd);
				cleanup(children[i]->root);
				exit(FAILURE);
			}
			exec_ast(children[i]);
		}
		close_pipes(fd, i, count);
	}
	return (waitpids(pids, count));
}

int	exec_pipe(t_ast **children)
{
	int		*pids;
	int		status;
	int		count;

	count = count_commands(children);
	pids = (int *) malloc(count * sizeof(int));
	status = run_pipe(children, pids, count);
	free(pids);
	return (status);
}
