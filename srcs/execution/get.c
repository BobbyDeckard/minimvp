/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:39:10 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 14:56:44 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

// compte le nombre de tokens dans la liste
int	count_args(t_token *ptr)
{
	int	count;

	count = 1;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

// parse de manière sommaire la liste de tokens en un tableau de strings
// où chaque élément de la liste de tokens est une string
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

// dupliques le path dans notre structure t_cmd et libère la string de
// la fonction précédente (c'est complètement con et superflu de faire ça)
void	found_cmd_path(t_cmd *cmd, char *path)
{
	cmd->path = ft_strdup(path);
	free(path);
}

// fonction qui join chacun des paths récupérés dans l'environnement avec le
// nom de l'exécutable recherché pour vérifier avec access() si le fichier
// existe
// s'il existe, appelle la fonction found_cmd_path pour sauvegarder le path
// s'il n'existe pas, free la string créée par ft_strjoin()
void	get_path(t_cmd *cmd, char **paths)
{
	char	*full_path;
	char	*name;
	int		i;

	name = cmd->args[0];
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
