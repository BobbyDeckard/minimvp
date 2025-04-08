/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:16 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/07 15:52:28 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;

	paths = get_paths();
	(void) ac;
	(void) av;
	(void) paths;
	(void) envp;
	ast = make_ast();
//	print_tree(*ast);
	exec_ast(ast, paths, envp);
	return (0);
}
