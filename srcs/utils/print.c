/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:35:00 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/04 15:52:02 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_node_type(t_ast node)
{
	int type;

	type = node.type;
	if (type == 0)
		printf("Command node\n");
	else if (type == 1)
		printf("Pipe node\n");
	else if (type == 2)
		printf("And-if node\n");
	else if (type == 3)
		printf("Or-if node\n");
	else if (type == 4)
		printf("Redir in node\n");
	else if (type == 5)
		printf("Redir out node\n");
	else if (type == 6)
		printf("Redir append node\n");
	else if (type == 7)
		printf("Heredoc node\n");

}

void	print_child(t_ast node)
{
	print_node_type(node);
	if (node.type == NODE_CMD)
		printf("%s\n", node.cmd.args[0]);
}

void	print_node_info(t_ast node)
{
	int	i;

	print_node_type(node);
	if (node.parent)
	{
		printf("Parent: ");
		print_node_type(*node.parent);
	}
	if (node.cmd.path)
		printf("Path:\n\t%s\n", node.cmd.path);
	if (node.cmd.args)
	{
		printf("Arguments:\n");
		i = -1;
		while (node.cmd.args[++i])
			printf("\t%s\n", node.cmd.args[i]);
	}
	if (node.type == NODE_CMD)
		printf("fd_in = %d\nfd_out = %d\n", node.cmd.fd_in, node.cmd.fd_out);
	if (node.file)
		printf("File: %s\n", node.file);
	if (node.children)
	{
		printf("Children:\n");
		i = -1;
		while (node.children[++i])
			print_child(*(node.children[i]));
	}
	printf("\n");
}

void	print_tree(t_ast ast)
{
	int	i;

	print_node_info(ast);
	if (ast.children)
	{
		i = -1;
		while (ast.children[++i])
			print_tree(*ast.children[i]);
	}
}
