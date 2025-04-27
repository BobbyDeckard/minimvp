/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/25 13:17:35 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	print_cmd(int mode)
{
	if (mode == 0)
		printf("cat file | grep foo\n");
	else if (mode == 1)
		printf("cat file | grep foo | grep bar | wc -l\n");
	else if (mode == 2)
		printf("< file wc -l > outfile\n");
	else if (mode == 3)
		printf("< file grep foo | wc -l > outfile\n");
	else if (mode == 4)
		printf("< file grep foo | grep bar | grep foobar | wc -l > outfile\n");
	printf("\n");
}

// La gestion des erreurs n'a pas encore été implémentée
int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;
	int		mode;

	if (ac != 2)
		return (1);
	mode = ft_atoi(av[1]);
	if (mode > 4)
		return (1);
	print_cmd(mode);
	paths = get_paths();
	ast = make_ast(mode);
//	print_tree(*ast);
	exec_ast(ast, paths, envp);
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
