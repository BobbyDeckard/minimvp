/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:27:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/27 13:59:02 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

// initialise la structure cmd avec des valeurs par défaut
t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.args = NULL;
	cmd.path = NULL;
	return (cmd);
}

void	clear_cmd(t_cmd *cmd)
{
	if (cmd->args)
		free_args(cmd->args);
	if (cmd->path)
		free(cmd->path);
}

// crée un procès enfant avec fork()
// appelle l'exécutable de la commande avec execve() dans le procès enfant
// le procès parent attend la fin du procès enfant avant de poursuivre
void	exec_cmd(t_cmd *cmd, char **envp)
{
	int	pid;

	if (cmd->path)
		pid = fork();
	else
		pid = -1;
	if (pid == 0)
		execve(cmd->path, cmd->args, envp);
	waitpid(pid, NULL, 0);
	clear_cmd(cmd);
}

void	print_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		printf("%s\n", args[i]);
}

// initialise la structure t_cmd
// crée le tableau de strings args et la string path
// exécute la commande
void	execute(t_token **token_list, char **envp)
{
	t_cmd	cmd;
	
	cmd = init_cmd();
	get_args(&cmd, token_list);
	get_path(&cmd);
	exec_cmd(&cmd, envp);
}
