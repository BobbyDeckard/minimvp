/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 17:50:36 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	*command;
	char	*cwd;
	int		preset;

	(void) ac;
	(void) av;
	
	while (1)
	{
		cwd = make_cwd();
		command = readline(cwd);
		free(cwd);
		if (command)
		{
			preset = ft_atoi(command);
			add_history(command);
			if (preset > 16 || !ft_isdigit(command[0]))
			{
				print_options();
				free(command);
			}
			else
			{
				free(command);
				print_cmd(preset);
				ast = make_ast(preset);
				ast->paths = get_paths();
				ast->envp = envp;
				exec_ast(ast);
				cleanup(ast->root);
			}
		}
		else
			break;
	}
	return (0);
}

/*
int main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;
	int		mode;

	if (ac != 2)
		return (1);
	mode = ft_atoi(av[1]);
	if (mode > 16)
	{
		printf("Invalid preset\n");
		return (1);
	}
	print_cmd(mode);
	paths = get_paths();
	ast = make_ast(mode);
	ast->paths = paths;
	ast->envp = envp;
//	print_tree(ast);
	exec_ast(ast);
	cleanup(ast);
	return (0);
}
*/
