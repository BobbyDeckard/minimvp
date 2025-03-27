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

t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.args = NULL;
	cmd.path = NULL;
	cmd.fd_in = -1;
	cmd.fd_out = -1;
	return (cmd);
}

void	clear_cmd(t_cmd *cmd)
{
	if (cmd->args)
		free_args(cmd->args);
	if (cmd->path)
		free(cmd->path);
}

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

}

void	print_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		printf("%s\n", args[i]);
}

void	execute(t_token **token_list, char **envp)
{
	t_cmd	cmd;
	
	cmd = init_cmd();
	get_args(&cmd, token_list);
	get_path(&cmd);
	exec_cmd(&cmd, envp);
}
