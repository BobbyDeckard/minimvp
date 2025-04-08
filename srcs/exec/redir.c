/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:54:50 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/04 16:17:06 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	make_redir_in(t_ast *redir, t_ast *child, char **paths, char **envp)
{
	if (access(redir->file, F_OK) || access(redir->file, R_OK))
		child->cmd.fd_in = -1;
	else
		child->cmd.fd_in = open(redir->file, O_RDONLY);
	if (child->cmd.fd_in < 0)
		perror(redir->file);
	close(child->cmd.fd_in);
	return (exec_cmd(child->cmd, paths, envp));
}

int	make_redir_out(t_ast *redir, t_ast *child, char **paths, char **envp)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK))
		child->cmd.fd_out = -1;
	else
		child->cmd.fd_out = open(redir->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (child->cmd.fd_out < 0)
		perror(redir->file);
	close(child->cmd.fd_out);
	return (exec_cmd(child->cmd, paths, envp));
}

int	make_redir_append(t_ast *redir, t_ast *child, char **paths, char **envp)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK))
		child->cmd.fd_out = -1;
	else
		child->cmd.fd_out = open(redir->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (child->cmd.fd_out < 0)
		perror(redir->file);
	close(child->cmd.fd_out);
	return (exec_cmd(child->cmd, paths, envp));
}
