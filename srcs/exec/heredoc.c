/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/13 19:40:44 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// << word
// reads input until it finds a line containing only word with no trailing blanks

int	check_and_open(char *name, t_ast *node)
{
	t_cmd	*cmd;
	
	cmd = &node->cmd;
	if (access(name, F_OK) == 0)
		return (0);
	cmd->fd_in = open(name, O_WRONLY | O_CREAT, 0644);
	node->file = name;
	if (cmd->fd_in < 0)
		perror(node->file);
	return (1);
}

int	open_temp(t_ast *node)
{
	if (check_and_open("tmp", node))
		return (SUCCESS);
	else if (check_and_open("temp", node))
		return (SUCCESS);
	else if (check_and_open("temporary_file", node))
		return (SUCCESS);
	return (FAILURE);
}

void	make_heredoc(t_ast *node)
{
	char	*line;
	char	*delimiter;
	int		len;

	line = NULL;
	delimiter = node->file;
	len = ft_strlen(delimiter);
	if (open_temp(node) == FAILURE)
		return ;
	while (ft_strncmp(line, delimiter, len))
	{
		line = readline(">");
		ft_putstr_fd(line, node->cmd.fd_in);
		ft_putchar_fd('\n', node->cmd.fd_in);
		free(line);
	}
	close(node->cmd.fd_in);
}
