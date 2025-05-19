MAKEFLAGS += --no-print-directory

NAME	=	build/cub3D

CC		=	cc
C_FLAGS	=	-Wall -Werror -Wextra
LIBS 	=	-lm -L mlx/ -lXext -lX11

SRC_DIR		=	source
OBJ_DIR		=	build/obj
HEADER_DIR	=	include
LIBFT_DIR	=	include/libft
LIBFT_LIB	=	include/libft/build/libft.a
MLX_DIR		=	minilibx-linux
MLX_LIB		=	$(MLX_DIR)/libmlx.a

EXECUTION	=	xpm raycast_utils raycast
PARSING		=	

SRC_FILES 	=	$(addsuffix .c, $(addprefix source/execution/, $(EXECUTION))) \
	  			$(addsuffix .c, $(addprefix source/parsing/, $(PARSING))) \
				source/main.c

OBJS 		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RESET		= \033[0m
GREEN		= \033[1;32m
RED			= \033[1;31m
BLUE		= \033[1;36m

#############################################################################################

all: $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
		@mkdir -p $(OBJ_DIR)
		@ar rcs $@ $^
		@echo -n "$(GREEN)█$(RESET)"
		@$(CC) $(CFLAGS) -o cub3D $(OBJ_DIR)/main.o $(NAME) $(LIBFT_LIB) $(MLX_LIB) $(LIBS)
		@echo -n "\n$(BLUE)READY TO EXECUTE.   $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		@echo -n "$(GREEN)█$(RESET)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
		@echo -n "$(GREEN)█"
		@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_LIB):
		@echo -n "$(GREEN)█"
		@$(MAKE) -s -C $(MLX_DIR)

clean:
		@rm -rf build
		@rm -f ./cub3D
		@$(MAKE) -s -C $(LIBFT_DIR) clean
		@$(MAKE) -s -C $(MLX_DIR) clean
		@echo "\n$(GREEN)ALL CLEANED UP.$(RESET)"

fclean:	clean
		@rm -f $(NAME)
		@$(MAKE) -s -C $(LIBFT_DIR) fclean
		@$(MAKE) -s -C $(MLX_DIR) fclean

re:		fclean all
		@echo "$(BLUE)PROJECT REBUILT.$(RESET)"

.PHONY:	all clean fclean re