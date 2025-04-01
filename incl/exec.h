/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:54:18 by imeulema          #+#    #+#             */
/*   Updated: 2025/04/02 00:46:28 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum
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
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			cmd;
}	t_ast;

/* Pseudo parsing functions */
t_ast *make_ast();
char	**ft_split_path(const char *s, char c);
char	**get_paths(void);

/* Execution functions */
void	exec_ast(t_ast *ast, char **paths, char **envp);
void	get_cmd_path(t_cmd *cmd, char **paths);

#endif
