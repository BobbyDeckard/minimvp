# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 14:35:02 by imeulema          #+#    #+#              #
#    Updated: 2025/03/31 18:58:57 by imeulema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minimvp
CC = cc
CFLAGS = -Wextra -Wall -Werror
LFLAGS = -lreadline
RM = rm
RMFLAGS = -f
MAKE = make
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	LFLAGS += -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include/readline
endif

# SOURCES
SRCS = $(addprefix $(PATH_SRCS), $(SRCS_FILES))
SRCS_FILES = main.c \
			 $(PARSING) \
			 $(UTILS) \
			 $(AST)
PATH_SRCS = srcs/
PATH_OBJS = objs/
OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

# SOURCE FILES
PARSING = $(addprefix parsing/, $(PARS_FILES))
PARS_FILES = caracter_type.c \
			 caracter_type2.c \
			 helpers.c \
			 parse.c \
			 retrieve.c \
			 tokenize.c \
			 tokenize2.c \
			 tokens.c \
			 $(SYNTAX_CHECK)
SYNTAX_CHECK = $(addprefix syntax_check/, $(SYNT_FILES))
SYNT_FILES = other_type_check.c \
			 parenthesis_check.c \
			 syntax_check.c
EXECUTION = $(addprefix execution/, $(EXEC_FILES))
EXEC_FILES = exec.c \
			 clean_pipex.c \
			 get.c \
			 get_pipe.c \
			 paths.c \
			 pipex.c
UTILS = $(addprefix utils/, $(UTIL_FILES))
UTIL_FILES = clear.c \
			 cwd.c \
			 ft_split_path.c
AST = $(addprefix ast/, $(AST_FILES))
AST_FILES = pseudo_parsing.c \
			exec_ast.c \
			paths.c

# INCLUDES
HEADERS = incl/mvp.h
LIBFT = libft/libft.a

# TERMINAL COLORS
RED = \033[0;31m
YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m

# RULES
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	echo "$(GREEN)$(NAME) compiled!$(RESET)"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft --no-print-directory

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(MAKE) clean -C libft --no-print-directory

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	$(MAKE) fclean -C libft --no-print-directory
	echo "$(GREEN)Full clean done.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

.SILENT:
