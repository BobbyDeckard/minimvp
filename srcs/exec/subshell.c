/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:14:05 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/13 16:41:38 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_subshell(t_ast *node)
{
	char	*path;
	char	*cwd;
	int		status;
	int		pid;
	int		len;

	status = -1;
	pid = fork();
	if (pid < 0)
		return (fork_error());
	if (pid == 0)
	{
		cwd = getcwd(NULL, 0);
		len = ft_strlen("/minimvp") + ft_strlen(cwd) + 1;
		path = (char *) malloc(len * sizeof(char));
		if (!path)
			malloc_error(node);
		ft_strlcat(path, cwd, len);
		ft_strlcat(path, "/minimvp", len);
		if (execve(path, NULL, node->root->envp) == -1)
			perror("execve");
		cleanup(node->root);
		exit(FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
