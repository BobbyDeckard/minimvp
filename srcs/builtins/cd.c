/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:34:18 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 17:14:13 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*cd_error(t_ast	*cd)
{
	t_cmd	cmd;
	char	*msg;
	int		len;

	cmd = cd->cmd;
	len = ft_strlen(cmd.args[1]);
	msg = (char *) malloc((len + 5) * sizeof(char));
	if (!msg)
		clean_exit(cd->root, FAILURE);
	ft_strlcpy(msg, "cd: ", len + 5);
	ft_strlcat(msg, cmd.args[1], len + 5);
	return (msg);
}

int	cd(t_ast *cd)
{
	char	*error;

	if (chdir(cd->cmd.args[1]) < 0)
	{
		error = cd_error(cd);
		perror(error);
		free(error);
		return (FAILURE);
	}
	return (SUCCESS);
}
