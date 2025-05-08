/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:31:04 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 13:02:58 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	echo(t_ast	*echo)
{
	int flag;
	int	i;

	if (make_redirs(echo, &echo->cmd) == FAILURE)
		return (FAILURE);
	flag = 0;
	if (!ft_strncmp(echo->cmd.args[1], "-n", echo->cmd.fd_out))
		flag++;
	i = flag;
	while (echo->cmd.args[++i])
	{
		ft_putstr_fd(echo->cmd.args[i], echo->cmd.fd_out);
		if (echo->cmd.args[i + 1])
			ft_putchar_fd(' ', echo->cmd.fd_out);
	}
	if (!flag)
		ft_putchar_fd('\n', echo->cmd.fd_out);
	close_redirs(echo->cmd);
	return (SUCCESS);
}
