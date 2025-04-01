/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:02:26 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/02 00:31:15 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

#include <string.h>
char **make_args(int count, ...) {
	// DO NOT SUBMIT THIS FILE
    va_list args;
    va_start(args, count);

    char **argv = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; i < count; i++)
        argv[i] = strdup(va_arg(args, char *));
    argv[count] = NULL;

    va_end(args);
    return argv;
}

t_ast *make_ast() {
    // echo "ok"
    t_ast *echo_ok = malloc(sizeof(t_ast));
    echo_ok->type = NODE_CMD;
    echo_ok->cmd.args = make_args(2, "echo", "ok");
	echo_ok->left = NULL;
	echo_ok->right = NULL;

    // ls
    t_ast *ls = malloc(sizeof(t_ast));
    ls->type = NODE_CMD;
    ls->cmd.args = make_args(1, "ls");
	ls->left = NULL;
	ls->right = NULL;

    // echo "fail"
    t_ast *echo_fail = malloc(sizeof(t_ast));
    echo_fail->type = NODE_CMD;
    echo_fail->cmd.args = make_args(2, "echo", "fail");
	echo_fail->left = NULL;
	echo_fail->right = NULL;

    // ls && echo "ok"
    t_ast *and_node = malloc(sizeof(t_ast));
    and_node->type = NODE_AND_IF;
    and_node->left = ls;
    and_node->right = echo_ok;

    // (ls && echo "ok") || echo "fail"
    t_ast *or_node = malloc(sizeof(t_ast));
    or_node->type = NODE_OR_IF;
    or_node->left = and_node;
    or_node->right = echo_fail;

    return or_node;
}

char	**get_paths(void)
{
	char	**paths;
	char	*all_paths;

	all_paths = getenv("PATH");
	paths = ft_split_path(all_paths, ':');	// need to secure those functions
	return (paths);
}
