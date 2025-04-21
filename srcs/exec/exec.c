/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:30:32 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/10 15:11:28 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// close function only used outside of pipes
void	close_fds2(t_cmd cmd)
{
	if (cmd.fd_in != STDIN_FILENO && cmd.fd_in >= 0)
		close(cmd.fd_in);
	if (cmd.fd_out != STDOUT_FILENO && cmd.fd_out >= 0)
		close(cmd.fd_out);
}

// only used outside of pipes
void	dup_fds2(t_cmd cmd)
{
	if (cmd.fd_in != STDIN_FILENO)
		dup2(cmd.fd_in, STDIN_FILENO);
	if (cmd.fd_out != STDOUT_FILENO)
		dup2(cmd.fd_out, STDOUT_FILENO);
	close_fds2(cmd);
}

void	exec_cmd(t_cmd cmd, char **paths, char **envp)
{
	get_cmd_path(&cmd, paths);
	if (!cmd.path)
	{
		ft_putstr_fd(cmd.args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	if (execve(cmd.path, cmd.args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

// only called for a single function outside pipelines
int	run_cmd(t_ast *ast, char **paths, char **envp)
{
	t_cmd	cmd;
	int		status;
	int		pid;

	cmd = ast->cmd;
	status = -1;
	make_redirs(ast, &cmd);
	if (cmd.fd_in < 0 || cmd.fd_out < 0)
	{
		close_fds2(cmd);
		return (FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (FAILURE); }
	if (pid == 0)
	{
		dup_fds2(cmd);
		exec_cmd(cmd, paths, envp);
	}
	close_fds2(cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

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
		if (exec_ast(children[i], paths, envp) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	exec_ast(t_ast *ast, char **paths, char **envp)
{
	if (ast->type == NODE_CMD)
		return (run_cmd(ast, paths, envp));
	else if (ast->type == NODE_OR_IF && ast->children)
		return (exec_or_if(ast->children, paths, envp));
	else if (ast->type == NODE_AND_IF && ast->children)
		return (exec_and_if(ast->children, paths, envp));
	else if (ast->type == NODE_PIPE && ast->children)
		return (exec_pipe(ast->children, paths, envp));
//	else if (ast->type == NODE_REDIR_IN && ast->children)
//		return (make_redir_in(ast, paths, envp));
//	else if (ast->type == NODE_REDIR_OUT && ast->children)
//		return (make_redir_out(ast, paths, envp));
//	else if (ast->type == NODE_REDIR_APPEND && ast->children)
//		return (make_redir_append(ast, paths, envp));
	return (FAILURE);
}
