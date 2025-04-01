/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:39:08 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/31 18:56:44 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

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

	name = cmd->argv[0];
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

void	exec_cmd(t_ast *ast, char **paths, char **envp)
{
	int	pid;

	get_path(&ast->cmd, paths);
	if (ast->cmd.path)
		pid = fork();
	else
		pid = -1;
	if (pid == 0)
	{
		if (!execve(ast->cmd.path, ast->cmd.argv, envp))
			exit (1);
	}
	waitpid(pid, NULL, 0);
}

void	exec_ast(t_ast *ast, char **paths, char **envp)
{
	if (ast->type == NODE_CMD)
		exec_cmd(ast, paths, envp);
	if (ast->left)
		exec_ast(ast->left, paths, envp);
	if (ast->right)
		exec_ast(ast->right, paths, envp);
}
