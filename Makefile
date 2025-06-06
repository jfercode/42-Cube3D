MAKEFLAGS += --no-print-directory

NAME	=	cub3D

IS_BONUS ?= 0 

CC		=	cc
C_FLAGS	=	-Wall -Werror -Wextra -g3 -O0 -DIS_BONUS=$(IS_BONUS)
LIBS 	=	-lm -L mlx/ -lXext -lX11


SRC_DIR		=	source
OBJ_DIR		=	build/obj
HEADER_DIR	=	include
LIBFT_DIR	=	include/libft
LIBFT_LIB	=	include/libft/build/libft.a
MLX_DIR		=	minilibx-linux
MLX_LIB		=	$(MLX_DIR)/libmlx.a

PARSING		=	file_validation texture_validation color_validation \
				parsing_utils map_storation map_validation map_closed_validation \
				memory_free door_validation
ERROR 		=	error_handling 
EXECUTION	=	init_vars xpm key_mapping raycast raycast_utils cleaner player_physics minimap

SRC_FILES 	=	$(addsuffix .c, $(addprefix source/execution/, $(EXECUTION))) \
	  			$(addsuffix .c, $(addprefix source/parsing/, $(PARSING))) \
	  			$(addsuffix .c, $(addprefix source/error_handling/, $(ERROR))) \
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

$(NAME): $(LIBFT_LIB) $(OBJS) $(MLX_LIB)
		@echo -n "$(GREEN)█$(RESET)"
		@$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LIBS)
		@echo -n "\n$(BLUE)READY TO EXECUTE.\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		@echo -n "$(GREEN)█$(RESET)"
		@$(CC) $(C_FLAGS) -c $< -o $@

$(LIBFT_LIB):
		@echo -n "$(GREEN)█"
		@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_LIB):
		@echo -n "$(GREEN)█"
		@$(MAKE) -s -C $(MLX_DIR)

bonus:
	@$(MAKE) re IS_BONUS=1

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

.PHONY:	all bonus clean fclean re 