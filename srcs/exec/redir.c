/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:54:50 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/10 10:41:35 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		cmd->cmd.fd_out = open(redir->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
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
		cmd->cmd.fd_out = open(redir->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (cmd->cmd.fd_out < 0)
		perror(redir->file);
	close(cmd->cmd.fd_out);
	return (exec_ast(redir->children[0], paths, envp));
}
