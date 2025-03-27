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

t_exec	init_exec(void)
{
	t_exec	exec;

	exec.args = NULL;
	exec.path = NULL;
	exec.fd_in = -1;
	exec.fd_out = -1;
	return (exec);
}

void	clear_exec(t_exec *exec)
{
	if (exec->args)
		free_args(exec->args);
	if (exec->path)
		free(exec->path);
}

void	exec_cmd(t_exec *exec, char **envp)
{
	int	pid;

	if (exec->path)
		pid = fork();
	else
		pid = -1;
	if (pid == 0)
		execve(exec->path, exec->args, envp);
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
	t_exec	exec;
	
	exec = init_exec();
	get_args(&exec, token_list);
	get_path(&exec);
	exec_cmd(&exec, envp);
}
