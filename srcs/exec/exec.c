/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:30:32 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/03 19:54:39 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_cmd(t_cmd cmd, char **paths, char **envp)
{
	int	pid;

	get_cmd_path(&cmd, paths);
	if (cmd.path)
		pid = fork();
	else
		pid = -1;
	if (pid == 0 && cmd.fd_in != -1 && cmd.fd_out != -1)
	{
		if (!execve(cmd.path, cmd.args, envp))
			return (FAILURE);
	}
	waitpid(pid, NULL, 0);
	return (SUCCESS);
}

// For following two functions, not sure which value to return.
// Need to do some testing on which command's exit status is returned to
// the previous node.
int	exec_or_if(t_ast **children, char **paths, char **envp)
{
	int	i;

	i = -1;
	while (children[++i])
	{
		if (exec_ast(children[i], paths, envp) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}

int	exec_and_if(t_ast **children, char **paths, char **envp)
{
	int	i;

	i = -1;
	while (children[++i])
	{
		if (exec_ast(children[i], paths, envp) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	exec_ast(t_ast *ast, char **paths, char **envp)
{
	if (ast->type == NODE_CMD)
		return (exec_cmd(ast->cmd, paths, envp));
	else if (ast->type == NODE_OR_IF && ast->children)
		return (exec_or_if(ast->children, paths, envp));
	else if (ast->type == NODE_AND_IF && ast->children)
		return (exec_and_if(ast->children, paths, envp));
	else if (ast->type == NODE_PIPE && ast->children)
		return (exec_pipe(ast->children, paths, envp));
	else if (ast->type == NODE_REDIR_IN && ast->children)
		return (make_redir_in(ast, ast->children[0], paths, envp));
	else if (ast->type == NODE_REDIR_OUT && ast->children)
		return (make_redir_out(ast, ast->children[0], paths, envp));
	else if (ast->type == NODE_REDIR_APPEND && ast->children)
		return (make_redir_append(ast, ast->children[0], paths, envp));
	return (FAILURE);
}
