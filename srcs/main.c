/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/05/08 13:44:47 by imeulema         ###   ########.fr       */
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
	if (mode > 15)
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
