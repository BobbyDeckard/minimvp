/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/15 10:21:42 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	set_parents(t_ast *ast);

// La gestion des erreurs n'a pas encore été implémentée
int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;

	(void) ac;
	(void) av;
	paths = get_paths();
	ast = make_ast();
	(void) envp;
	(void) paths;
	set_parents(ast);
	print_tree(*ast);
//	exec_ast(ast, paths, envp);
	return (0);
}

/*
t_ast	*make_ast_from_input(const char *input);

int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;
	char	*command;
	char	*cwd;

	(void) ac;
	(void) av;
	paths = get_paths();
	while (1)
	{
		cwd = make_cwd();
		command = readline(cwd);
		free(cwd);
		if (command)
		{
			add_history(command);
			ast = make_ast_from_input(command);
			exec_ast(ast, paths, envp);
			free(command);
		}
		else
			break;
	}
	return (0);
}
*/
