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
	char	**paths;
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
			paths = get_paths();
			preset = ft_atoi(command);
			add_history(command);
			if (preset > 16 || !ft_isdigit(command[0]))
			{
				printf("Invalid preset, please enter a number between 0 and 16 (included) to simulate the following presets:\n");
				printf("0:\tcat file | grep foo\n");
				printf("1:\tcat file | grep foo | grep bar | wc -l\n");
				printf("2:\t< file wc -l > outfile\n");
				printf("3:\t< file grep foo | wc -l > outfile\n");
				printf("4:\t< file grep foo | grep bar | grep foobar | wc -l > outfile\n");
				printf("5:\tcat file && echo ok\n");
				printf("6:\tcat file || echo fail\n");
				printf("7:\tcat file && echo ok || echo fail\n");
				printf("8:\t< infile grep foo | wc -l > outfile && echo ok || echo fail\n");
				printf("9:\tcat file | (grep foo && grep bar)\n");
				printf("10:\tcat file | (grep foo || grep bar)\n");
				printf("11:\tcat file | (cat infile && grep foo)\n");
				printf("12\techo -n hello\n");
				printf("13\techo hello there > outfile\n");
				printf("14:\techo hello there | wc -w\n");
				printf("15:\tcd srcs && pwd\n");
				printf("16:\tenv\n");
			}
			free(command);
			print_cmd(preset);
			ast = make_ast(preset);
			ast->paths = paths;
			ast->envp = envp;
			exec_ast(ast);
			cleanup(ast);
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
