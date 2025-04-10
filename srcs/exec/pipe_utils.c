/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:56:56 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/10 12:39:57 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	make_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	return (1);
}

int	waitpids(int *pids, int cmd_count)
{
	int status;
	int	i;

	i = -1;
	while (++i < cmd_count)
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = -1;
	return (status);
}

int	count_commands(t_ast **children)
{
	int	i;

	i = 0;
	while (children[i])
		i++;
	return (i);
}

void	close_pipes(int fd[2][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}
