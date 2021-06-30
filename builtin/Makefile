NAME	=	sunashell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE = -I./includes
SRC		=	main.c tree.c debug.c term.c \
			builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c \
			builtin/export.c builtin/pwd.c builtin/unset.c \
			utils/lib.c utils/lib2.c utils/lib3.c utils/parsing.c \
			error_handler/error_handler.c error_handler/syntax_error.c utils/quote.c \
			shell/run_redirection.c shell/execve.c

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
	@printf "\b\b\b\b\b\b\b\b\b\b\b\b\033\e[1;33mSU\e[1;31mNA\e[1;37mSHELL \e[0;32mis Ready 💚\e[0m\n"


bonus	: all

clean	:
			@rm -f $(OBJ)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean	all

.PHONY	:	all clean fclean re bonus
