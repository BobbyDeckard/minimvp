/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/27 18:52:47 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;
	int		mode;

	if (ac != 2)
		return (1);
	mode = ft_atoi(av[1]);
	if (mode > 7)
		return (1);
	print_cmd(mode);
	paths = get_paths();
	ast = make_ast(mode);
	ast->paths = paths;
	ast->envp = envp;
//	print_tree(*ast);
	exec_ast(ast);
	cleanup(ast);
	return (0);
}

// Fonction main appelant des fonctions chatgptisées pour simuler
// un parsing.
// Notre programme aura sans doute un main suivant cette forme générale.
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
