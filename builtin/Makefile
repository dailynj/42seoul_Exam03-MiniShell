# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:01:44 by najlee            #+#    #+#              #
#    Updated: 2021/07/15 14:31:34 by najlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE = -I./includes
SRC		=	main.c debug.c term.c history.c signal.c start_command.c\
			builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c \
			builtin/export.c builtin/pwd.c builtin/unset.c \
			utils/lib.c utils/lib2.c utils/lib3.c utils/lib4.c utils/lib5.c \
			error_handler/error_handler.c error_handler/syntax_error.c \
			shell/run_redirection.c shell/run_redirection2.c shell/execve.c \
			list/list1.c list/list2.c list/list3.c\
			parsing/parsing.c parsing/parsing2.c parsing/parsing3.c parsing/quote.c parsing/quote2.c \
			parsing/input.c parsing/input2.c

SRC_DIR = ./src/
SHELL	= bash
SRCS = $(addprefix $(SRC_DIR),$(SRC))

# OBJ = $(SRCS:.c=.o)

all		:	$(NAME)

%.o		:	$(SRC_DIR)/%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	# @./wave.sh
	# @./spinner.sh
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(NAME)
	@printf "\b\b\b\b\b\b\b\b\b\b\b\b\033m\e[1;33mMI\e[1;31mNI\e[1;37mSHELL \e[0;32mis Ready 💚\e[0m\n"


bonus	: all

clean	:
			@rm -f $(OBJ)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean	all

.PHONY	:	all clean fclean re bonus
