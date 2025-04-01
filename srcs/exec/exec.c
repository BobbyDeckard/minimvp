/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:30:32 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/02 00:45:48 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	exec_cmd(t_cmd cmd, char **paths, char **envp)
{
	int	pid;

	get_cmd_path(&cmd, paths);
	if (cmd.path)
		pid = fork();
	else
		pid = -1;
	if (pid == 0)
	{
		if (!execve(cmd.path, cmd.args, envp))
			exit (1);
	}
	waitpid(pid, NULL, 0);
}

void	exec_ast(t_ast *ast, char **paths, char **envp)
{
	if (ast->type == NODE_CMD)
		exec_cmd(ast->cmd, paths, envp);
	if (ast->left)
		exec_ast(ast->left, paths, envp);
	if (ast->right)
		exec_ast(ast->right, paths, envp);
}
