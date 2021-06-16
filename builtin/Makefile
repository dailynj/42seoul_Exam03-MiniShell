NAME	=	minishell

CC		=	gcc
CF		=	-Wall -Wextra -Werror -I ./includes
SRC1	=	push_swap.c list_util_1.c list_util_2.c \
			instruction_1.c instruction_2.c libft_1.c error_check.c \
			quick_sort.c  sort_1.c sort_3.c free.c \
			push_tail_srp_1.c push_tail_srp_2.c free_2.c cmd.c libft_2.c \
			sort_a.c sort_b.c classification_a.c classification_b.c \

SRC2	=	checker.c list_util_1.c list_util_2.c \
			instruction_1.c instruction_2.c libft_1.c error_check.c \
			quick_sort.c  sort_1.c sort_3.c free.c \
			push_tail_srp_1.c push_tail_srp_2.c free_2.c cmd.c libft_2.c \
			sort_a.c sort_b.c classification_a.c classification_b.c \

SRC_DIR = ./src/

SRCS1 = $(addprefix $(SRC_DIR),$(SRC1))
SRCS2 = $(addprefix $(SRC_DIR),$(SRC2))

OBJ1 = $(SRCS1:.c=.o)
OBJ2 = $(SRCS2:.c=.o)

all		:	$(NAME1) $(NAME2)

%.o		:	$(SRC_DIR)/%.c
			$(CC) $(CF) -c $< -o $@

$(NAME1): $(OBJ)
	$(CC) $(CF) $(SRCS1) -o $(NAME1)

$(NAME2): $(OBJ)
	$(CC) $(CF) $(SRCS2) -o $(NAME2)

clean	:
			rm -f $(OBJ1) $(OBJ2)

fclean	:	clean
			rm -f $(NAME1)
			rm -f $(NAME2)

re		:	fclean	all

.PHONY	:	all clean fclean re
