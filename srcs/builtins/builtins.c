/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:37:06 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 17:25:10 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_builtin(t_ast *cmd)
{
	char	*name;

	if (!cmd->cmd.args)
		return (FAILURE);
	name = cmd->cmd.args[0];
	if (!ft_strncmp(name, "echo", 5))
		return (echo(cmd));
	else if (!ft_strncmp(name, "cd", 3))
		return (cd(cmd));
	else if (!ft_strncmp(name, "pwd", 4))
		return (pwd());
	else if (!ft_strncmp(name, "export", 7))
		return (1);
	else if (!ft_strncmp(name, "unset", 6))
		return (1);
	else if (!ft_strncmp(name, "env", 4))
		return (1);
	else if (!ft_strncmp(name, "exit", 5))
		return (1);
	return (FAILURE);
}

int	is_builtin(t_cmd cmd)
{
	char	*name;

	if (!cmd.args)
		return (0);
	name = cmd.args[0];
	if (!ft_strncmp(name, "echo", 5))
		return (1);
	else if (!ft_strncmp(name, "cd", 3))
		return (1);
	else if (!ft_strncmp(name, "pwd", 4))
		return (1);
//	else if (!ft_strncmp(name, "export", 7))
//		return (1);
//	else if (!ft_strncmp(name, "unset", 6))
//		return (1);
//	else if (!ft_strncmp(name, "env", 4))
//		return (1);
//	else if (!ft_strncmp(name, "exit", 5))
//		return (1);
	return (0);
}
