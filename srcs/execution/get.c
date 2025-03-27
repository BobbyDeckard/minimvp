/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:39:10 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/27 13:40:36 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

int	count_args(t_token *token_list)
{
	int	count;

	count = 1;
	while (token_list)
	{
		count++;
		token_list = token_list->next;
	}
	return (count);
}

void	get_args(t_cmd *cmd, t_token **token_list)
{
	t_token	*ptr;
	int		count;
	int		i;

	count = count_args(*token_list);
	cmd->args = (char **) malloc(count * sizeof(char *));
	if (!cmd->args)
		exit (1);
	ptr = *token_list;
	i = -1;
	while (++i + 1 < count)
	{
		cmd->args[i] = ptr->content;
		ptr = ptr->next;
	}
	cmd->args[i] = NULL;
}

void	found_cmd_path(t_cmd *cmd, char *path)
{
	cmd->path = ft_strdup(path);
	free(path);
}

void	find_cmd_path(t_cmd *cmd, char **paths, char *name)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], name);
		if (access(full_path, F_OK) == 0)
			return (found_cmd_path(cmd, full_path));
		free(full_path);
	}
	printf("minishell: %s: command not found\n", name);
}

void	get_path(t_cmd *cmd)
{
	char	**paths;
	char	*str;

	str = getenv("PATH");
	paths = ft_split_path(str, ':');
	// split paths only once and keep array somewhere
	find_cmd_path(cmd, paths, cmd->args[0]);
}
