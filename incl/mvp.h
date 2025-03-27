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

/* MVP structure prototype */
typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		fd_in;
	int		fd_out;
}	t_cmd;

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

/* Token struct */
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

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
char	*make_cwd(void);
void	execute(t_token **token_list, char **envp);
void	free_args(char **args);
void	get_args(t_exec *exec, t_token **token_list);
void	get_path(t_exec *exec);

#endif
