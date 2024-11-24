
NAME = cub
BONUS = cub_bonus
CC = cc
CFLAGS =  -Wall -Wextra -Werror #fsanitize=address -g3 
SRC = mandatory/cub3d.c mandatory/get_start.c mandatory/draw_pixels.c mandatory/hooks.c \
		mandatory/rotate.c mandatory/texture_handling.c\
		mandatory/player_movement.c mandatory/ray_casting.c \
		mandatory/horizontal.c mandatory/vertical.c mandatory/key_hooks.c \
		mandatory/parsing/general_utils.c mandatory/parsing/map_parsing.c \
		mandatory/parsing/parser.c mandatory/parsing/parsing_utils.c \
		mandatory/parsing/read_file.c
SRC_BONUS = bonus/cub.c bonus/get_start.c bonus/draw_pixels.c bonus/hooks.c \
		bonus/rotate.c bonus/texture_handling.c\
		bonus/player_moves.c bonus/ray_casting.c bonus/utils.c \
		bonus/horizontal.c bonus/vertical.c bonus/key_hooks.c \
		bonus/parsing/general_utils.c bonus/parsing/map_parsing.c \
		bonus/parsing/parser.c bonus/parsing/parsing_utils.c \
		bonus/parsing/read_file.c
CC = cc
MLX1 = minilibx/libmlx_Linux.a -lXext -lX11 -lm
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_OBJ = $(shell cat libft/Makefile | grep "ft_" | tr -d '\\' | tr -d "\n" \
			| tr "\t" " " |tr -s ' ' | sed 's/ / libft\//g' | sed 's/\.c/\.o/g')

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX1) -o $(NAME)

$(BONUS): libft $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX1) -o $(BONUS)

libft: $(LIBFT_OBJ)
		make bonus -C libft/

all: $(NAME)

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS) && make clean -C libft

fclean: clean
	rm -f $(NAME) $(BONUS) && make fclean -C libft

re: fclean all
