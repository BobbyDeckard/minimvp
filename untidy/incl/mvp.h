#ifndef MVP_H
# define MVP_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"

/* Token typology */
typedef enum
{
	DEFAULT = 0,    /* Initial state */
	WORD = 1,       /* Commands and arguments */
	ASSIGNMENT = 2, /* Variable assignments */
	
	QUOTE = 3,        /* Generic quote */
	SINGLE_QUOTE = 4, /* 'string' */
	DOUBLE_QUOTE = 5, /* "string" */
	
	REDIR = 6,        /* Generic redirection */
	REDIR_IN = 7,     /* < */
	REDIR_OUT = 8,    /* > */
	REDIR_APPEND = 9, /* >> */
	HEREDOC = 10,     /* << */
	
	OPERATOR = 11,  /* Generic operator */
	PIPE = 12,      /* | */
	AND = 13,       /* && */
	OR = 14,        /* || */
	
	PARENTHESIS = 15,  /* Generic parenthesis */
	PAREN_OPEN = 16,   /* ( */
	PAREN_CLOSE = 17,  /* ) */
	
	SPECIAL_CARACTER = 18, /* Special characters */
	ENV_VAR = 19,         /* $VAR */
	EXIT_STATUS = 20,     /* $? */
	ESCAPE = 21,          /* \ (backslash) */
	COMMENT = 22,         /* # */
	T_NEWLINE = 23,       /* End of command */
	T_EOF = 24,           /* End of input */
	
	UNKNOWN = 25     /* Error handling */
}	t_token_type;

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

typedef struct s_redir
{
	t_node_type		type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/* Token struct */
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd {
    char	**argv;         // NULL-terminated array of arguments
	char	*path;
    t_redir	*redirs;        // redirection list
} t_cmd;

/* my own cmd struct */
/* Command struct */
//typedef struct s_cmd
//{
//	char	**args;
//	char	*path;
//	int		fdin;
//	int		fdout;
//}	t_cmd;

typedef struct s_ast
{
	t_node_type	type;
	struct s_ast *left;
	struct s_ast *right;
	t_cmd	cmd;
}	t_ast;

/* Pipe struct */
typedef struct s_pip
{
	char	**cmd1_args;
	char	**cmd2_args;
	char	**paths;
	char	*cmd1_path;
	char	*cmd2_path;
	int		fd[2];
	int		fdin;
	int		fdout;
}	t_pip;

/* I-TOKENIZATION */

/* Retrieve */
t_token          **tokenize_input(char *command);
t_token          **extract_token(char **command, t_token_type type, 
				t_token **token_list);
t_token          *handle_token_type(char **command, t_token_type type, 
				t_token *new_token);

/* Tokenize */
t_token          *tokenize_word(char **command, t_token *token);
t_token          *tokenize_quote(char **command, t_token *token);
t_token          *tokenize_redir(char **command, t_token *token);
t_token          *tokenize_operator(char **command, t_token *token);
t_token          *tokenize_parenthesis(char **command, t_token *token);
t_token          *tokenize_special_caracter(char **command, t_token *token);
void             define_special_caracter(char **command, t_token *token);
void             define_double_redirection(char **command, t_token *token, 
				int *len);
void             define_bonus_operator(char **command, t_token *token, int *len);

/* Tokens */
t_token			*create_token(void);
void			link_token(t_token *token, t_token **token_list);
void			free_token(t_token *token);
void			free_token_list(t_token **token_list);

/* Characters */
int              is_space(char c);
int              is_quote(char c);
int              is_redirection(char c);
int              is_operator(char c);
int              is_command_char(char c);
int              is_parenthesis(char c);
int              is_special_caracter(char c);

/* Helpers */
int              find_word_len(char *content);

/* II-SYNTAX CHECK */

/* 1) PARENTHESIS */
/* Specific syntax checks by type */
int              paren_syntax_is_valid(t_token **token_list);
int				count_tokens(t_token **token_list);
int				check_token(t_token *cur, t_token **stack, int *top);
int              paren_syntax_is_valid(t_token **token_list);
int				quote_syntax_is_valid(t_token **token_list);
int				redir_syntax_is_valid(t_token **token_list);
int				operator_syntax_is_valid(t_token **token_list);
/*Overall syntax check*/
int				syntax_is_valid(t_token **token_list);

/* III-PARSE*/
/*Read */
void			read_command();
void			parse_input();
void			print_token_list(t_token **token_list);

/* IV-EXECUTION */
/* General use functions */
char	**ft_split_path(const char *s, char c);
//char	*make_cwd(void);
//void	execute(t_token **token_list, char **envp, char **paths);
//void	free_args(char **args);
//void	get_args(t_cmd *cmd, t_token **token_list);
//void	get_pipe_args(t_cmd *cmd1, t_cmd *cmd2, t_token **token_list);
//void	get_path(t_cmd *cmd, char **paths);
char	**split_paths(void);
void	exec_ast(t_ast *ast, char **paths, char **envp);

/* Pipe functions */
//void	clean_exit_pipe(t_pip *pip);
//void	clean_up_pipe(t_pip *pip);
//void	close_fds(t_pip *pip);
//void	free_args_pipe(char **args);
//void	pipex(t_cmd *cmd1, t_cmd *cmd2, char **envp);

#endif
