/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:54:26 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/15 10:23:30 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>			// autorisé ?
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>			// autorisé ?
# include "../libft/libft.h"

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

/* Enums */
typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND_IF,
	NODE_OR_IF,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}	t_node_type;

/* Structs */
typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	**children;
	t_cmd			cmd;
	char			*file;
}	t_ast;

/* Pseudo parsing functions */
t_ast	*make_ast();
char	**ft_split_path(const char *s, char c);
char	**get_paths(void);

/* Execution functions */
void	get_cmd_path(t_cmd *cmd, char **paths);
int		exec_ast(t_ast *ast, char **paths, char **envp);
int		exec_cmd(t_cmd cmd, char **paths, char **envp);
int		exec_pipe(t_ast **children, char **paths, char **envp);
int		make_redir_append(t_ast *redir, char **paths, char **envp);
int		make_redir_in(t_ast *redir, char **paths, char **envp);
int		make_redir_out(t_ast *redir, char **paths, char **envp);

/* Utilities functions */
void	print_tree(t_ast ast);
char	*make_cwd(void);

/* Pipe functions */
void	close_pipes(int fd[2][2], int i, int count);
int		count_commands(t_ast **children);
int		make_fork(void);
int		make_pipe(int fd[2]);
int		waitpids(int *pids, int count);


#include <string.h>

t_ast	*parse_command(char **tokens, int *i);
t_ast	*parse_pipe(char **tokens, int *i);
t_ast	*parse_and_or(char **tokens, int *i);
t_ast	*make_ast_from_input(const char *input);

#endif
