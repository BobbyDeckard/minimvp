/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:31:48 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 15:42:38 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

void	close_fds(t_pip *pip)
{
	if (pip->fdin != STDIN_FILENO)
	{
		close(pip->fdin);
		pip->fdin = STDIN_FILENO;
	}
	if (pip->fdout != STDOUT_FILENO)
	{
		close(pip->fdout);
		pip->fdout = STDOUT_FILENO;
	}
	if (pip->fd[0] != -1)
	{
		close(pip->fd[0]);
		pip->fd[0] = -1;
	}
	if (pip->fd[1] != -1)
	{
		close(pip->fd[1]);
		pip->fd[1] = -1;
	}
}

void	free_args_pipe(char **args)
{
	char	**ptr;

	ptr = args;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(args);
}

void	clean_up_pipe(t_pip *pip)
{
	if (pip->cmd1_args)
		free_args_pipe(pip->cmd1_args);
	if (pip->cmd2_args)
		free_args_pipe(pip->cmd2_args);
	if (pip->cmd1_path)
		free(pip->cmd1_path);
	if (pip->cmd2_path)
		free(pip->cmd2_path);
}

void	clean_exit_pipe(t_pip *pip)
{
	clean_up_pipe(pip);
	exit(1);
}
