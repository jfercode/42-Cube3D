NAME		=	libft.a
FLAG		=	-Wall -Wextra -Werror

SRC			=	*.c		
DIR_OBJ		=	obj/
OBJ			=	$(SRC:%.c=$(DIR_OBJ)%.o)

RESET		=	\033[0m
GREEN		=	\033[1;32m

##############################

all: ${NAME}

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(DIR_OBJ)%.o: %.c
	@mkdir -p $(dir $@)
	@cc $(FLAG) -c $< -o $@
	@echo -n "$(GREEN)█$(RESET)"

clean:
	@rm -f $(OBJ) $(BONUSOBJ)

fclean: clean
	@rm -f $(NAME)

re: all fclean

.PHONY: all clean fclean re bonus
