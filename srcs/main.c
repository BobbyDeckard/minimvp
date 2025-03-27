/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:18:22 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/27 13:40:22 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -lreadline to compile readline
#include "../incl/mvp.h"

int main(int ac, char **av, char **envp)
{
    t_token **token_list;
    char    *command;
    char    *cwd;

	(void) ac;
	(void) av;
    while (1)
    {
	cwd = make_cwd();
	command = readline(cwd);
	free(cwd);
	if (command)
	{
	    add_history(command);
	    token_list = tokenize_input(command);
	    execute(token_list, envp);
	    free_token_list(token_list);
	    free(command);
	}
	else
	    break;
    }
    return (0);
}
