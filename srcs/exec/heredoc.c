/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/13 20:12:18 by imeulema         ###   ########.fr       */
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
	printf("Created %s\n", name);
	return (1);
}

int	file_namer_2000(t_ast *node)
{
	char	name[128];
	int		i;
	int		j;

	i = -1;
	while (++i < 128)
		name[i] = 0;
	i = -1;
	while (++i < 128)
	{
		j = 0;
		while (++j < 128)
		{
			name[i] = j;
			if (check_and_open(name, node))
				return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	open_temp(t_ast *node)
{
	if (check_and_open("tmp", node))
		return (SUCCESS);
	else if (check_and_open("temp", node))
		return (SUCCESS);
	else if (check_and_open("temporary_file", node))
		return (SUCCESS);
	else if (check_and_open("heredoc", node))
		return (SUCCESS);
	else if (check_and_open("here", node))
		return (SUCCESS);
	else if (check_and_open("hrdoc", node))
		return (SUCCESS);
	return (FAILURE);
}

void	make_heredoc(t_ast *node)
{
	char	*line;
	char	*delimiter;
	int		len;

	delimiter = node->file;
	len = ft_strlen(delimiter) + 1;
	if (file_namer_2000(node) == FAILURE)
		return ;
	printf("delimiter = %s\nlen = %d\n", delimiter, len);
	while (1)
	{
		line = readline(">");
		ft_putstr_fd(line, node->cmd.fd_in);
		ft_putchar_fd('\n', node->cmd.fd_in);
		if (!ft_strncmp(line, delimiter, len))
			break ;
		free(line);
	}
	free(line);
	printf("Exiting make_heredoc\n");
}
