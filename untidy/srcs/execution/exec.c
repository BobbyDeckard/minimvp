/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:27:44 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 16:22:54 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mvp.h"

// initialise la structure cmd avec des valeurs par défaut
t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.args = NULL;
	cmd.path = NULL;
	cmd.fdin = STDIN_FILENO;
	cmd.fdout = STDOUT_FILENO;
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
void	execute_single(t_token **token_list, char **envp, char **paths)
{
	t_cmd	cmd;
	
	cmd = init_cmd();
	get_args(&cmd, token_list);
	get_path(&cmd, paths);
	exec_cmd(&cmd, envp);
}

void	execute_simple_pipe(t_token **token_list, char **envp, char **paths)
{
	t_cmd	cmd1;
	t_cmd	cmd2;

	cmd1 = init_cmd();
	cmd2 = init_cmd();
	get_pipe_args(&cmd1, &cmd2, token_list);
	get_path(&cmd1, paths);
	get_path(&cmd2, paths);
	pipex(&cmd1, &cmd2, envp);
}

int		get_exec_type(t_token **token_list)
{
	t_token	*ptr;

	ptr = *token_list;
	while (ptr)
	{
		if (ptr->type == 12)
			return (2);
		else if (ptr->type != 1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void	execute(t_token **token_list, char **envp, char **paths)
{
	int	exec_type;

	exec_type = get_exec_type(token_list);
	if (exec_type == 1)
		execute_single(token_list, envp, paths);
	else if (exec_type == 2)
		execute_simple_pipe(token_list, envp, paths);
	return ;
}
