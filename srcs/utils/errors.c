#include "../../incl/minishell.h"

// Returns FAILURE to keep the rest of the execution running.
int	fork_error(void)
{
	perror("fork");
	return (FAILURE);
}

// Here we can use exit() because dup2() is only called in child processes.
void	dup2_error(void)
{
	perror("dup2");
	exit(FAILURE);
}

int	pipe_error(int *pids, int fd[2][2], int i, int count)
{
	close_pipes(fd, i, count);
	waitpids(pids, count);
	return (FAILURE);
}

void	malloc_error(t_ast *ast)
{
	perror("malloc");
	clean_exit(ast->root, FAILURE);
}
