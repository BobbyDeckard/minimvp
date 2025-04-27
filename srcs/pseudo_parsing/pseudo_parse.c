/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:02:26 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/15 10:24:08 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

void	set_parents(t_ast *ast)
{
	int	i;

	if (ast->children)
	{
		i = -1;
		while (ast->children[++i])
		{
			ast->children[i]->parent = ast;
			set_parents(ast->children[i]);
		}
	}
}

/* DEMOS */

/*
// Redirections
t_ast	*make_ast(void)
{
	t_ast	*redir;
	redir = (t_ast *) malloc(sizeof(t_ast));
	if (!redir)
		exit(1);
	redir->type = NODE_REDIR_IN;
	redir->children = NULL;
	redir->file = "file";

	t_ast	*cmd;
	cmd = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd)
		exit(1);
	cmd->type = NODE_CMD;
	cmd->cmd.args = make_args(2, "grep", "foo");
	cmd->cmd.fd_in = STDIN_FILENO;
	cmd->cmd.fd_out = STDOUT_FILENO;
	cmd->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!cmd->children)
		exit(1);
	cmd->children[0] = redir;
	cmd->children[1] = NULL;
	cmd->file = NULL;

	return (cmd);
}
*/

/*
// (cat file | grep foo | wc -l > outfile && echo "The number of lines containing foo in file is:" && cat outfile) || echo "Fail"
t_ast	*make_ast(void)
{
	t_ast	*cat_file;
	cat_file = (t_ast *) malloc(sizeof(t_ast));
	if (!cat_file)
		exit(1);
	cat_file->type = NODE_CMD;
	cat_file->cmd.args = make_args(2, "cat", "file");
	cat_file->cmd.fd_in = STDIN_FILENO;
	cat_file->cmd.fd_out = STDOUT_FILENO;
	cat_file->children = NULL;
	cat_file->file = NULL;

	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	if (!grep)
		exit(1);
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*wc;
	wc = (t_ast *) malloc(sizeof(t_ast));
	if (!wc)
		exit(1);
	wc->type = NODE_CMD;
	wc->cmd.args = make_args(2, "wc", "-l");
	wc->cmd.fd_in = STDIN_FILENO;
	wc->cmd.fd_out = STDOUT_FILENO;
	wc->children = NULL;
	wc->file = NULL;

	t_ast	*echo_foo;
	echo_foo = (t_ast *) malloc(sizeof(t_ast));
	if (!echo_foo)
		exit(1);
	echo_foo->type = NODE_CMD;
	echo_foo->cmd.args = make_args(2, "echo", "The number of lines containing foo in file is:");
	echo_foo->cmd.fd_in = STDIN_FILENO;
	echo_foo->cmd.fd_out = STDOUT_FILENO;
	echo_foo->children = NULL;
	echo_foo->file = NULL;

	t_ast	*cat_out;
	cat_out = (t_ast *) malloc(sizeof(t_ast));
	if (!cat_out)
		exit(1);
	cat_out->type = NODE_CMD;
	cat_out->cmd.args = make_args(2, "cat", "outfile");
	cat_out->cmd.fd_in = STDIN_FILENO;
	cat_out->cmd.fd_out = STDOUT_FILENO;
	cat_out->children = NULL;
	cat_out->file = NULL;

	t_ast	*echo_fail;
	echo_fail = (t_ast *) malloc(sizeof(t_ast));
	if (!echo_fail)
		exit(1);
	echo_fail->type = NODE_CMD;
	echo_fail->cmd.args = make_args(2, "echo", "Fail");
	echo_fail->cmd.fd_in = STDIN_FILENO;
	echo_fail->cmd.fd_out = STDOUT_FILENO;
	echo_fail->children = NULL;
	echo_fail->file = NULL;

	t_ast	*out;
	out = (t_ast *) malloc(sizeof(t_ast));
	if (!out)
		exit(1);
	out->type = NODE_REDIR_OUT;
	out->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!out->children)
		exit(1);
	out->children[0] = wc;
	out->children[1] = NULL;
	out->file = "outfile";

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->children = (t_ast **) malloc(4 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = cat_file;
	pipe->children[1] = grep;
	pipe->children[2] = wc;
	pipe->children[3] = NULL;
	pipe->file = NULL;

	t_ast	*and2;
	and2 = (t_ast *) malloc(sizeof(t_ast));
	if (!and2)
		exit(1);
	and2->type = NODE_AND_IF;
	and2->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and2->children)
		exit(1);
	and2->children[0] = echo_foo;
	and2->children[1] = out;
	and2->children[2] = NULL;
	and2->file = NULL;
	
	t_ast	*and1;
	and1 = (t_ast *) malloc(sizeof(t_ast));
	if (!and1)
		exit(1);
	and1->type = NODE_AND_IF;
	and1->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and1->children)
		exit(1);
	and1->children[0] = pipe;
	and1->children[1] = and2;
	and1->children[2] = NULL;
	and1->file = NULL;

	t_ast	*or;
	or = (t_ast *) malloc(sizeof(t_ast));
	if (!or)
		exit(1);
	or->type = NODE_OR_IF;
	or->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!or->children)
		exit(1);
	or->children[0] = and1;
	or->children[1] = echo_fail;
	or->children[2] = NULL;
	or->file = NULL;

	return (or);
}
*/

/* Simple pipe
t_ast	*make_ast(void)
{
	t_ast	*cat;
	cat = (t_ast *) malloc(sizeof(t_ast));
	cat->type = NODE_CMD;
	cat->cmd.args = make_args(2, "cat", "file");
	cat->cmd.fd_in = STDIN_FILENO;
	cat->cmd.fd_out = STDOUT_FILENO;
	cat->children = NULL;
	cat->file = NULL;

	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*grep_bar;
	grep_bar = (t_ast *) malloc(sizeof(t_ast));
	grep_bar->type = NODE_CMD;
	grep_bar->cmd.args = make_args(2, "grep", "bar");
	grep_bar->cmd.fd_in = STDIN_FILENO;
	grep_bar->cmd.fd_out = STDOUT_FILENO;
	grep_bar->children = NULL;
	grep_bar->file = NULL;

	t_ast	*wc;
	wc = (t_ast *) malloc(sizeof(t_ast));
	wc->type = NODE_CMD;
	wc->cmd.args = make_args(2, "wc", "-w");
	wc->cmd.fd_in = STDIN_FILENO;
	wc->cmd.fd_out = STDOUT_FILENO;
	wc->children = NULL;
	wc->file = NULL;

	t_ast	*out;
	out = (t_ast *) malloc(sizeof(t_ast));
	if (!out)
		exit(1);
	out->type = NODE_REDIR_OUT;
	out->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!out->children)
		exit(1);
	out->children[0] = wc;
	out->children[1] = NULL;
	out->file = "outfile";

	t_ast	*echo;
	echo = (t_ast *) malloc(sizeof(t_ast));
	if (!echo)
		exit(1);
	echo->type = NODE_CMD;
	echo->cmd.args = make_args(2, "echo", "ok");
	echo->cmd.fd_in = STDIN_FILENO;
	echo->cmd.fd_out = STDOUT_FILENO;
	echo->children = NULL;
	echo->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->children = (t_ast **) malloc(5 * sizeof(t_ast *));
	pipe->children[0] = cat;
	pipe->children[1] = grep;
	pipe->children[2] = grep_bar;
	pipe->children[3] = out;
	pipe->children[4] = NULL;
	pipe->file = NULL;

	t_ast	*and;
	and = (t_ast *) malloc(sizeof(t_ast));
	if (!and)
		exit(1);
	and->type = NODE_AND_IF;
	and->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and->children)
		exit(1);
	and->children[0] = pipe;
	and->children[1] = echo;
	and->children[2] = NULL;
	and->file = NULL;

	return (and);
}
*/

/* Logical operators: ((cat file | grep foo) && echo ok) || echo fail
t_ast	*make_ast(void)
{
	t_ast	*cat;
	cat = (t_ast *) malloc(sizeof(t_ast));
	cat->type = NODE_CMD;
	cat->cmd.args = make_args(2, "cat", "file");
	cat->cmd.fd_in = STDIN_FILENO;
	cat->cmd.fd_out = STDOUT_FILENO;
	cat->children = NULL;
	cat->file = NULL;

	t_ast	*echo_ok;
	echo_ok = (t_ast *) malloc(sizeof(t_ast));
	echo_ok->type = NODE_CMD;
	echo_ok->cmd.args = make_args(2, "echo", "ok");
	echo_ok->cmd.fd_in = STDIN_FILENO;
	echo_ok->cmd.fd_out = STDOUT_FILENO;
	echo_ok->children = NULL;
	echo_ok->file = NULL;

	t_ast	*echo_fail;
	echo_fail = (t_ast *) malloc(sizeof(t_ast));
	echo_fail->type = NODE_CMD;
	echo_fail->cmd.args = make_args(2, "echo", "fail");
	echo_fail->cmd.fd_in = STDIN_FILENO;
	echo_fail->cmd.fd_out = STDOUT_FILENO;
	echo_fail->children = NULL;
	echo_fail->file = NULL;

	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	pipe->children[0] = cat;
	pipe->children[1] = grep;
	pipe->children[2] = NULL;
	pipe->file = NULL;

	t_ast	*and;
	and = (t_ast *) malloc(sizeof(t_ast));
	and->type = NODE_AND_IF;
	and->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	and->children[0] = pipe;
	and->children[1] = echo_ok;
	and->children[2] = NULL;
	and->file = NULL;

	t_ast	*or;
	or = (t_ast *) malloc(sizeof(t_ast));
	or->type = NODE_OR_IF;
	or->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	or->children[0] = and;
	or->children[1] = echo_fail;
	or->children[2] = NULL;
	or->file = NULL;

	return (or);
}
*/

//(ls -l | grep minishell) && echo "Found" || echo "Not found"
/*t_ast	*make_ast(void)
{
	t_ast	*ls = malloc(sizeof(t_ast));
	ls->type = NODE_CMD;
	ls->cmd.args = make_args(2, "ls", "-l");
	ls->cmd.fd_in = STDIN_FILENO;
	ls->cmd.fd_out = STDOUT_FILENO;
	ls->children = NULL;
	ls->file = NULL;

	t_ast	*grep = malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "minishell");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*echo_found = malloc(sizeof(t_ast));
	echo_found->type = NODE_CMD;
	echo_found->cmd.args = make_args(2, "echo", "Found");
	echo_found->cmd.fd_in = STDIN_FILENO;
	echo_found->cmd.fd_out = STDOUT_FILENO;
	echo_found->children = NULL;
	echo_found->file = NULL;

	t_ast	*echo_not_found = malloc(sizeof(t_ast));
	echo_not_found->type = NODE_CMD;
	echo_not_found->cmd.args = make_args(2, "echo", "Not found");
	echo_not_found->cmd.fd_in = STDIN_FILENO;
	echo_not_found->cmd.fd_out = STDOUT_FILENO;
	echo_not_found->children = NULL;
	echo_not_found->file = NULL;

	t_ast	*pipe = malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->children = malloc(3 * sizeof(t_ast *));
	pipe->children[0] = ls;
	pipe->children[1] = grep;
	pipe->children[2] = NULL;
	pipe->file = NULL;

	t_ast	*and = malloc(sizeof(t_ast));
	and->type = NODE_AND_IF;
	and->children = malloc(3 * sizeof(t_ast *));
	and->children[0] = pipe;
	and->children[1] = echo_found;
	and->children[2] = NULL;
	and->file = NULL;

	t_ast	*or = malloc(sizeof(t_ast));
	or->type = NODE_OR_IF;
	or->children = malloc(3 * sizeof(t_ast *));
	or->children[0] = and;
	or->children[1] = echo_not_found;
	or->children[2] = NULL;
	or->file = NULL;

	return (or);
}*/


/* multiple sleep
t_ast	*make_ast(void)
{
	t_ast	*sleep;
	sleep = (t_ast *) malloc(sizeof(t_ast));
	sleep->type = NODE_CMD;
	sleep->cmd.args = make_args(2, "sleep", "5");
	sleep->cmd.fd_in = STDIN_FILENO;
	sleep->cmd.fd_out = STDOUT_FILENO;
	sleep->children = NULL;
	sleep->file = NULL;

	t_ast	*in;
	in = (t_ast *) malloc(sizeof(t_ast));
	in->type = NODE_REDIR_IN;
	in->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	in->children[0] = sleep;
	in->children[1] = NULL;
	in->file = "infile";

	t_ast	*out;
	out = (t_ast *) malloc(sizeof(t_ast));
	out->type = NODE_REDIR_OUT;
	out->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	out->children[0] = sleep;
	out->children[1] = NULL;
	out->file = "outfile";

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(7 * sizeof(t_ast *));
	pipe->children[0] = in;
	pipe->children[1] = sleep;
	pipe->children[2] = sleep;
	pipe->children[3] = sleep;
	pipe->children[4] = out;
	pipe->children[5] = NULL;
	pipe->file = NULL;

	return (pipe);
}
*/

/* < infile grep foo | wc -l > outfile
t_ast	*make_ast(void)
{
	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*wc;
	wc = (t_ast *) malloc(sizeof(t_ast));
	wc->type = NODE_CMD;
	wc->cmd.args = make_args(2, "wc", "-w");
	wc->cmd.fd_in = STDIN_FILENO;
	wc->cmd.fd_out = STDOUT_FILENO;
	wc->children = NULL;
	wc->file = NULL;

	t_ast	*in;
	in = (t_ast *) malloc(sizeof(t_ast));
	in->type = NODE_REDIR_IN;
	in->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	in->children[0] = grep;
	in->children[1] = NULL;
	in->file = "infile";

	t_ast	*out;
	out = (t_ast *) malloc(sizeof(t_ast));
	out->type = NODE_REDIR_OUT;
	out->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	out->children[0] = wc;
	out->children[1] = NULL;
	out->file = "outfile";

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	pipe->children[0] = in;
	pipe->children[1] = out;
	pipe->children[2] = NULL;
	pipe->file = NULL;

	return (pipe);
}
*/

/* < infile grep foo >> outfile
t_ast	*make_ast(void)
{
	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = NULL;
	grep->file = NULL;

	t_ast	*out;
	out = (t_ast *) malloc(sizeof(t_ast));
	out->type = NODE_REDIR_APPEND;
	out->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	out->children[0] = grep;
	out->children[1] = NULL;
	out->file = "outfile";

	t_ast	*in;
	in = (t_ast *) malloc(sizeof(t_ast));
	in->type = NODE_REDIR_IN;
	in->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	in->children[0] = out;
	in->children[1] = NULL;
	in->file = "infile";

	return (in);
}
*/

/*
// < file grep foo | grep bar | grep foobar | wc -l
t_ast	*make_ast(void)
{
	t_ast	*redir;
	redir = (t_ast *) malloc(sizeof(t_ast));
	if (!redir)
		exit(1);
	redir->type = NODE_REDIR_IN;
	redir->children = NULL;
	redir->file = "file";

	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!grep->children)
		exit(1);
	grep->children[0] = redir;
	grep->children[1] = NULL;
	grep->file = NULL;

	t_ast	*grep_bar;
	grep_bar = (t_ast *) malloc(sizeof(t_ast));
	grep_bar->type = NODE_CMD;
	grep_bar->cmd.args = make_args(2, "grep", "bar");
	grep_bar->cmd.fd_in = STDIN_FILENO;
	grep_bar->cmd.fd_out = STDOUT_FILENO;
	grep_bar->children = NULL;
	grep_bar->file = NULL;

	t_ast	*grep_foobar;
	grep_foobar = (t_ast *) malloc(sizeof(t_ast));
	grep_foobar->type = NODE_CMD;
	grep_foobar->cmd.args = make_args(2, "grep", "foobar");
	grep_foobar->cmd.fd_in = STDIN_FILENO;
	grep_foobar->cmd.fd_out = STDOUT_FILENO;
	grep_foobar->children = NULL;
	grep_foobar->file = NULL;

	t_ast	*wc;
	wc = (t_ast *) malloc(sizeof(t_ast));
	wc->type = NODE_CMD;
	wc->cmd.args = make_args(2, "wc", "-l");
	wc->cmd.fd_in = STDIN_FILENO;
	wc->cmd.fd_out = STDOUT_FILENO;
	wc->children = NULL;
	wc->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(5 * sizeof(t_ast *));
	pipe->children[0] = grep;
	pipe->children[1] = grep_bar;
	pipe->children[2] = grep_foobar;
	pipe->children[3] = wc;
	pipe->children[4] = NULL;
	pipe->file = NULL;

	return (pipe);
}
*/

/* cat file && echo "ok" || echo "fail"
t_ast	*make_ast(void)
{
    t_ast *cat;
	cat = malloc(sizeof(t_ast));
    cat->type = NODE_CMD;
    cat->cmd.args = make_args(2, "cat", "file");
	cat->cmd.fd_in = STDIN_FILENO;
	cat->cmd.fd_out = STDOUT_FILENO;
	cat->children = NULL;
	cat->file = NULL;

    t_ast *echo_ok;
	echo_ok = malloc(sizeof(t_ast));
    echo_ok->type = NODE_CMD;
    echo_ok->cmd.args = make_args(2, "echo", "ok");
	echo_ok->cmd.fd_in = STDIN_FILENO;
	echo_ok->cmd.fd_out = STDOUT_FILENO;
	echo_ok->children = NULL;
	echo_ok->file = NULL;

    t_ast *echo_fail;
	echo_fail = malloc(sizeof(t_ast));
    echo_fail->type = NODE_CMD;
    echo_fail->cmd.args = make_args(2, "echo", "fail");
	echo_fail->cmd.fd_in = STDIN_FILENO;
	echo_fail->cmd.fd_out = STDOUT_FILENO;
	echo_fail->children = NULL;
	echo_fail->file = NULL;
	
    t_ast *and_node;
	and_node = malloc(sizeof(t_ast));
    and_node->type = NODE_AND_IF;
	and_node->children = (t_ast **) malloc(3 * sizeof(t_ast));
	and_node->children[0] = cat;
    and_node->children[1] = echo_ok;
	and_node->children[2] = NULL;
	and_node->file = NULL;

    t_ast *or_node;
	or_node = malloc(sizeof(t_ast));
    or_node->type = NODE_OR_IF;
	or_node->children = (t_ast **) malloc(3 * sizeof(t_ast));
    or_node->children[0] = and_node;
    or_node->children[1] = echo_fail;
	or_node->children[2] = NULL;
	or_node->file = NULL;

	return (or_node);
}
*/
