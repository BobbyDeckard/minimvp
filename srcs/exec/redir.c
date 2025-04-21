/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:54:50 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/10 10:43:53 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
t_ast	*get_next_cmd(t_ast *ast)
{
	while (ast && ast->type != NODE_CMD)
		ast = ast->children[0];
	return (ast);
}

int	make_redir_in(t_ast *redir, char **paths, char **envp)
{
	t_ast	*cmd;

	cmd = get_next_cmd(redir);
	if (access(redir->file, F_OK) || access(redir->file, R_OK))
		cmd->cmd.fd_in = -1;
	else
		cmd->cmd.fd_in = open(redir->file, O_RDONLY);
	if (cmd->cmd.fd_in < 0)
		perror(redir->file);
	return (exec_ast(redir->children[0], paths, envp));
}

int	make_redir_out(t_ast *redir, char **paths, char **envp)
{
	t_ast	*cmd;

	cmd = get_next_cmd(redir);
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK))
		cmd->cmd.fd_out = -1;
	else
	{
		cmd->cmd.fd_out = open(redir->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		cmd->file = redir->file;
	}
	if (cmd->cmd.fd_out < 0)
		perror(redir->file);
	return (exec_ast(redir->children[0], paths, envp));
}

int	make_redir_append(t_ast *redir, char **paths, char **envp)
{
	t_ast	*cmd;

	cmd = get_next_cmd(redir);
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK))
		cmd->cmd.fd_out = -1;
	else
	{
		cmd->cmd.fd_out = open(redir->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		cmd->file = redir->file;
	}
	if (cmd->cmd.fd_out < 0)
		perror(redir->file);
	return (exec_ast(redir->children[0], paths, envp));
}
*/

void	make_redir_in(t_ast *redir, t_cmd *cmd)
{
	if (access(redir->file, F_OK) != 0 || access(redir->file, R_OK) != 0)
		cmd->fd_in = -1;
	else
		cmd->fd_in = open(redir->file, O_RDONLY);
	if (cmd->fd_in < 0)
		perror(redir->file);
}

void	make_redir_out(t_ast *redir, t_cmd *cmd)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) != 0)
		cmd->fd_out = -1;
	else
		cmd->fd_out = open(redir->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (cmd->fd_out < 0)
		perror(redir->file);
}

void	make_redir_append(t_ast *redir, t_cmd *cmd)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) != 0)
		cmd->fd_out = -1;
	else
		cmd->fd_out = open(redir->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (cmd->fd_out < 0)
		perror(redir->file);
}

void	make_redirs(t_ast *ast, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ast->children)
	{
		while (ast->children[++i])
		{
			if (ast->children[i]->type == NODE_REDIR_IN)
				make_redir_in(ast->children[i], cmd);
			else if (ast->children[i]->type == NODE_REDIR_OUT)
				make_redir_out(ast->children[i], cmd);
			else if (ast->children[i]->type == NODE_REDIR_APPEND)
				make_redir_append(ast->children[i], cmd);
		}
	}
}
