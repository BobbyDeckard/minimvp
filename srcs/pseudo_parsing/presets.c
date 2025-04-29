/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:07:27 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/27 18:07:06 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include <unistd.h>

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

void	set_root_node(t_ast *ast, t_ast *root)
{
	int	i;

	ast->root = root;
	if (ast->children)
	{
		i = -1;
		while (ast->children[++i])
			set_root_node(ast->children[i], root);
	}
}

t_ast	*make_simple_pipe(void)
{
	// cat file | grep foo
	
	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "cat", "file");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "grep", "foo");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = cmd1;
	pipe->children[1] = cmd2;
	pipe->children[2] = NULL;
	pipe->file = NULL;
	
	set_root_node(pipe, pipe);

	return (pipe);
}

t_ast	*make_multi_pipe(void)
{
	// cat file | grep foo | grep bar | wc -l

	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "cat", "file");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "grep", "foo");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*cmd3;
	cmd3 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd3)
		exit(1);
	cmd3->type = NODE_CMD;
	cmd3->cmd.args = make_args(2, "grep", "bar");
	cmd3->cmd.fd_in = STDIN_FILENO;
	cmd3->cmd.fd_out = STDOUT_FILENO;
	cmd3->children = NULL;
	cmd3->file = NULL;

	t_ast	*cmd4;
	cmd4 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd4)
		exit(1);
	cmd4->type = NODE_CMD;
	cmd4->cmd.args = make_args(2, "wc", "-l");
	cmd4->cmd.fd_in = STDIN_FILENO;
	cmd4->cmd.fd_out = STDOUT_FILENO;
	cmd4->children = NULL;
	cmd4->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(5 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = cmd1;
	pipe->children[1] = cmd2;
	pipe->children[2] = cmd3;
	pipe->children[3] = cmd4;
	pipe->children[4] = NULL;
	pipe->file = NULL;
	
	set_root_node(pipe, pipe);

	return (pipe);
}

t_ast	*make_double_redirs(void)
{
	// < file wc -l > outfile

	t_ast	*redir_in;
	redir_in = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_in)
		exit(1);
	redir_in->type = NODE_REDIR_IN;
	redir_in->cmd.args = NULL;
	redir_in->children = NULL;
	redir_in->file = "file";

	t_ast	*redir_out;
	redir_out = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_out)
		exit(1);
	redir_out->type = NODE_REDIR_OUT;
	redir_out->cmd.args = NULL;
	redir_out->children = NULL;
	redir_out->file = "outfile";

	t_ast	*cmd;
	cmd = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd)
		exit(1);
	cmd->type = NODE_CMD;
	cmd->cmd.args = make_args(2, "wc", "-l");
	cmd->cmd.fd_in = STDIN_FILENO;
	cmd->cmd.fd_out = STDOUT_FILENO;
	cmd->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!cmd->children)
		exit(1);
	cmd->children[0] = redir_in;
	cmd->children[1] = redir_out;
	cmd->children[2] = NULL;
	cmd->file = NULL;

	set_root_node(cmd, cmd);

	return (cmd);
}

t_ast	*make_double_redirs_simple_pipe(void)
{
	// < file grep foo | wc -l > outfile

	t_ast	*redir_in;
	redir_in = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_in)
		exit(1);
	redir_in->type = NODE_REDIR_IN;
	redir_in->cmd.args = NULL;
	redir_in->children = NULL;
	redir_in->file = "file";

	t_ast	*redir_out;
	redir_out = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_out)
		exit(1);
	redir_out->type = NODE_REDIR_OUT;
	redir_out->cmd.args = NULL;
	redir_out->children = NULL;
	redir_out->file = "outfile";

	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "grep", "foo");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!cmd1->children)
		exit(1);
	cmd1->children[0] = redir_in;
	cmd1->children[1] = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "wc", "-l");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!cmd2->children)
		exit(1);
	cmd2->children[0] = redir_out;
	cmd2->children[1] = NULL;
	cmd2->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = cmd1;
	pipe->children[1] = cmd2;
	pipe->children[2] = NULL;
	pipe->file = NULL;
	
	set_root_node(pipe, pipe);

	return (pipe);
}

t_ast	*make_double_redirs_multi_pipe(void)
{
	// < file grep foo | grep bar | grep foobar | wc -l > outfile

	t_ast	*redir_in;
	redir_in = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_in)
		exit(1);
	redir_in->type = NODE_REDIR_IN;
	redir_in->cmd.args = NULL;
	redir_in->children = NULL;
	redir_in->file = "file";

	t_ast	*redir_out;
	redir_out = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_out)
		exit(1);
	redir_out->type = NODE_REDIR_OUT;
	redir_out->cmd.args = NULL;
	redir_out->children = NULL;
	redir_out->file = "outfile";

	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "grep", "foo");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!cmd1->children)
		exit(1);
	cmd1->children[0] = redir_in;
	cmd1->children[1] = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "grep", "bar");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*cmd3;
	cmd3 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd3)
		exit(1);
	cmd3->type = NODE_CMD;
	cmd3->cmd.args = make_args(2, "grep", "foobar");
	cmd3->cmd.fd_in = STDIN_FILENO;
	cmd3->cmd.fd_out = STDOUT_FILENO;
	cmd3->children = NULL;
	cmd3->file = NULL;

	t_ast	*cmd4;
	cmd4 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd4)
		exit(1);
	cmd4->type = NODE_CMD;
	cmd4->cmd.args = make_args(2, "wc", "-l");
	cmd4->cmd.fd_in = STDIN_FILENO;
	cmd4->cmd.fd_out = STDOUT_FILENO;
	cmd4->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!cmd4->children)
		exit(1);
	cmd4->children[0] = redir_out;
	cmd4->children[1] = NULL;
	cmd4->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(5 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = cmd1;
	pipe->children[1] = cmd2;
	pipe->children[2] = cmd3;
	pipe->children[3] = cmd4;
	pipe->children[4] = NULL;
	pipe->file = NULL;

	set_root_node(pipe, pipe);
	
	return (pipe);
}

t_ast	*make_and_if(void)
{
	// cat file && echo ok

	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "cat", "file");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "echo", "ok");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*and;
	and = (t_ast *) malloc(sizeof(t_ast));
	if (!and)
		exit(1);
	and->type = NODE_AND_IF;
	and->cmd.args = NULL;
	and->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and->children)
		exit(1);
	and->children[0] = cmd1;
	and->children[1] = cmd2;
	and->children[2] = NULL;
	and->file = NULL;
	
	set_root_node(and, and);

	return (and);
}

t_ast	*make_or_if(void)
{
	// cat file || echo fail

	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "cat", "file");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "echo", "fail");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*or;
	or = (t_ast *) malloc(sizeof(t_ast));
	if (!or)
		exit(1);
	or->type = NODE_OR_IF;
	or->cmd.args = NULL;
	or->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!or->children)
		exit(1);
	or->children[0] = cmd1;
	or->children[1] = cmd2;
	or->children[2] = NULL;
	or->file = NULL;
	
	set_root_node(or, or);

	return (or);
}

t_ast	*make_and_or_if(void)
{
	// cat file && echo ok || echo fail
	
	t_ast	*cmd1;
	cmd1 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd1)
		exit(1);
	cmd1->type = NODE_CMD;
	cmd1->cmd.args = make_args(2, "cat", "file");
	cmd1->cmd.fd_in = STDIN_FILENO;
	cmd1->cmd.fd_out = STDOUT_FILENO;
	cmd1->children = NULL;
	cmd1->file = NULL;

	t_ast	*cmd2;
	cmd2 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd2)
		exit(1);
	cmd2->type = NODE_CMD;
	cmd2->cmd.args = make_args(2, "echo", "ok");
	cmd2->cmd.fd_in = STDIN_FILENO;
	cmd2->cmd.fd_out = STDOUT_FILENO;
	cmd2->children = NULL;
	cmd2->file = NULL;

	t_ast	*cmd3;
	cmd3 = (t_ast *) malloc(sizeof(t_ast));
	if (!cmd3)
		exit(1);
	cmd3->type = NODE_CMD;
	cmd3->cmd.args = make_args(2, "echo", "fail");
	cmd3->cmd.fd_in = STDIN_FILENO;
	cmd3->cmd.fd_out = STDOUT_FILENO;
	cmd3->children = NULL;
	cmd3->file = NULL;

	t_ast	*and;
	and = (t_ast *) malloc(sizeof(t_ast));
	if (!and)
		exit(1);
	and->type = NODE_AND_IF;
	and->cmd.args = NULL;
	and->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and->children)
		exit(1);
	and->children[0] = cmd1;
	and->children[1] = cmd2;
	and->children[2] = NULL;
	and->file = NULL;
	
	t_ast	*or;
	or = (t_ast *) malloc(sizeof(t_ast));
	if (!or)
		exit(1);
	or->type = NODE_OR_IF;
	or->cmd.args = NULL;
	or->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!or->children)
		exit(1);
	or->children[0] = and;
	or->children[1] = cmd3;
	or->children[2] = NULL;
	or->file = NULL;
	
	set_root_node(or, or);

	return (or);
}

t_ast	*make_demo(void)
{
	t_ast	*redir_in;
	redir_in = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_in)
		exit(1);
	redir_in->type = NODE_REDIR_IN;
	redir_in->cmd.args = NULL;
	redir_in->children = NULL;
	redir_in->file = "infile";
	
	t_ast	*redir_out;
	redir_out = (t_ast *) malloc(sizeof(t_ast));
	if (!redir_out)
		exit(1);
	redir_out->type = NODE_REDIR_OUT;
	redir_out->cmd.args = NULL;
	redir_out->children = NULL;
	redir_out->file = "outfile";

	t_ast	*grep;
	grep = (t_ast *) malloc(sizeof(t_ast));
	if (!grep)
		exit(1);
	grep->type = NODE_CMD;
	grep->cmd.args = make_args(2, "grep", "foo");
	grep->cmd.fd_in = STDIN_FILENO;
	grep->cmd.fd_out = STDOUT_FILENO;
	grep->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!grep->children)
		exit(1);
	grep->children[0] = redir_in;
	grep->children[1] = NULL;
	grep->file = NULL;

	t_ast	*wc;
	wc = (t_ast *) malloc(sizeof(t_ast));
	if (!wc)
		exit(1);
	wc->type = NODE_CMD;
	wc->cmd.args = make_args(2, "wc", "-l");
	wc->cmd.fd_in = STDIN_FILENO;
	wc->cmd.fd_out = STDOUT_FILENO;
	wc->children = (t_ast **) malloc(2 * sizeof(t_ast *));
	if (!wc->children)
		exit(1);
	wc->children[0] = redir_out;
	wc->children[1] = NULL;
	wc->file = NULL;

	t_ast	*echo_ok;
	echo_ok = (t_ast *) malloc(sizeof(t_ast));
	if (!echo_ok)
		exit(1);
	echo_ok->type = NODE_CMD;
	echo_ok->cmd.args = make_args(2, "echo", "ok");
	echo_ok->cmd.fd_in = STDIN_FILENO;
	echo_ok->cmd.fd_out = STDOUT_FILENO;
	echo_ok->children = NULL;
	echo_ok->file = NULL;

	t_ast	*echo_fail;
	echo_fail = (t_ast *) malloc(sizeof(t_ast));
	if (!echo_fail)
		exit(1);
	echo_fail->type = NODE_CMD;
	echo_fail->cmd.args = make_args(2, "echo", "fail");
	echo_fail->cmd.fd_in = STDIN_FILENO;
	echo_fail->cmd.fd_out = STDOUT_FILENO;
	echo_fail->children = NULL;
	echo_fail->file = NULL;

	t_ast	*pipe;
	pipe = (t_ast *) malloc(sizeof(t_ast));
	if (!pipe)
		exit(1);
	pipe->type = NODE_PIPE;
	pipe->cmd.args = NULL;
	pipe->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!pipe->children)
		exit(1);
	pipe->children[0] = grep;
	pipe->children[1] = wc;
	pipe->children[2] = NULL;

	t_ast	*and;
	and = (t_ast *) malloc(sizeof(t_ast));
	if (!and)
		exit(1);
	and->type = NODE_AND_IF;
	and->cmd.args = NULL;
	and->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!and->children)
		exit(1);
	and->children[0] = pipe;
	and->children[1] = echo_ok;
	and->children[2] = NULL;
	and->file = NULL;

	t_ast	*or;
	or = (t_ast *) malloc(sizeof(t_ast));
	if (!or)
		exit(1);
	or->type = NODE_OR_IF;
	or->cmd.args = NULL;
	or->children = (t_ast **) malloc(3 * sizeof(t_ast *));
	if (!or->children)
		exit(1);
	or->children[0] = and;
	or->children[1] = echo_fail;
	or->children[2] = NULL;
	or->file = NULL;

	set_root_node(or, or);

	return (or);
}

t_ast	*make_ast(int mode)
{
	if (mode == 0)
		return (make_simple_pipe());
	else if (mode == 1)
		return (make_multi_pipe());
	else if (mode == 2)
		return (make_double_redirs());
	else if (mode == 3)
		return (make_double_redirs_simple_pipe());
	else if (mode == 4)
		return (make_double_redirs_multi_pipe());
	else if (mode == 5)
		return (make_and_if());
	else if (mode == 6)
		return (make_or_if());
	else if (mode == 7)
		return (make_and_or_if());
	else if (mode == 8)
		return (make_demo());
	else
		return (NULL);
}
