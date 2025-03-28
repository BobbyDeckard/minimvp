/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:18:22 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/28 14:58:58 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -lreadline to compile readline
#include "../incl/mvp.h"

int main(int ac, char **av, char **envp)
{
	t_token	**token_list;
	char	**paths;
	char	*command;
	char	*cwd;

	(void) ac;
	(void) av;
	paths = split_paths();
	while (1)
	{
		cwd = make_cwd();
		command = readline(cwd);
		free(cwd);
		if (command)
		{
			add_history(command);
			token_list = tokenize_input(command);
			execute(token_list, envp, paths);
//			free_token_list(token_list);
			free(command);
		}
		else
			break;
	}
	return (0);
}
