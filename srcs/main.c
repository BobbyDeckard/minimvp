/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:18:22 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/31 22:55:27 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -lreadline to compile readline
#include "../incl/mvp.h"

t_ast	*make_logical_ast();

void	print_args(t_cmd cmd)
{
	int		i;

	i = -1;
	printf("Command %s, args:\n", cmd.argv[0]);
	while (cmd.argv[++i])
		printf("%s ", cmd.argv[i]);
	printf("\n");
}

void	print_tree(t_ast *ast)
{
	if (ast->type == NODE_CMD)
		print_args(ast->cmd);
	else if (ast->type == NODE_AND_IF)
		printf("Node and if\n");
	else if (ast->type == NODE_OR_IF)
		printf("Node or if\n");
	if (!ast->left && !ast->right)
		return ;
	if (ast->left)
		print_tree(ast->left);
	if (ast->right)
		print_tree(ast->right);
}

int	main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	**paths;

	paths = split_paths();
	(void) ac;
	(void) av;
	ast = make_logical_ast();
//	print_tree(ast);
	exec_ast(ast, paths, envp);
	return 0;
}

/*
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
*/
