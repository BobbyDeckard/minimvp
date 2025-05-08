/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:16:33 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 17:30:12 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pwd(t_ast *pwd)
{
	char	*cwd;

	if (make_redirs(pwd, &pwd->cmd) == FAILURE)
		return (FAILURE);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		close_redirs(pwd->cmd);
		return (FAILURE);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	close_redirs(pwd->cmd);
	return (SUCCESS);
}
