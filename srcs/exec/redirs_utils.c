/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:44:32 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/13 20:12:16 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	close_redirs(t_ast *child, t_cmd cmd)
{
	if (cmd.fd_in != STDIN_FILENO && cmd.fd_in >= 0)
		close(cmd.fd_in);
//	if (child->type == NODE_HEREDOC)
//		unlink(child->file);
	if (cmd.fd_out != STDOUT_FILENO && cmd.fd_out >= 0)
		close(cmd.fd_out);
	(void) child;
}

int	check_redirs(t_ast *child, t_cmd cmd)
{
	if (cmd.fd_in < 0 || cmd.fd_out < 0)
	{
		close_redirs(child, cmd);
		return (FAILURE);
	}
	return (SUCCESS);
}

