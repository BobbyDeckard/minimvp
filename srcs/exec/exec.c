/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:30:32 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/27 19:08:07 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	exec_cmd(t_ast *ast, t_cmd cmd)
{
	get_cmd_path(&cmd, ast->root->paths);
	if (!cmd.path)
	{
		ft_putstr_fd(cmd.args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	if (execve(cmd.path, cmd.args, ast->root->envp) == -1)
		perror("execve");
}

int	run_cmd(t_ast *ast)
{
	int		status;
	int		pid;

	status = -1;
	pid = fork();
	if (pid < 0)
		return (fork_error());
	if (pid == 0)
	{
		if (make_redirs(ast, &ast->cmd) == FAILURE)
			return (FAILURE);
		printf("fd_in = %d\n", ast->cmd.fd_in);
		dup_fds(*ast);
		exec_cmd(ast, ast->cmd);
		cleanup(ast->root);
		exit(FAILURE);
	}
	close_redirs(ast->cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	exec_or_if(t_ast **children)
{
	int	i;

	i = -1;
	while (children[++i])
	{
		if (exec_ast(children[i]) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}

int	exec_and_if(t_ast **children)
{
	int	i;

	i = -1;
	while (children[++i])
	{
		if (exec_ast(children[i]) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	exec_ast(t_ast *ast)
{
	if (ast->type == NODE_CMD)
		return (run_cmd(ast));
	else if (ast->type == NODE_OR_IF && ast->children)
		return (exec_or_if(ast->children));
	else if (ast->type == NODE_AND_IF && ast->children)
		return (exec_and_if(ast->children));
	else if (ast->type == NODE_PIPE && ast->children)
		return (exec_pipe(ast->children));
	return (FAILURE);
}
