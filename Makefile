
NAME = cub3d
BONUS = cub3d_bonus
CC = cc
CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3
SRC = mandatory/cub3d.c mandatory/get_start.c mandatory/draw_pixels.c mandatory/hooks.c \
		mandatory/rotate.c mandatory/texture_handling.c\
		mandatory/player_movement.c mandatory/ray_casting.c \
		mandatory/horizontal.c mandatory/vertical.c mandatory/key_hooks.c \
		mandatory/parsing/general_utils.c mandatory/parsing/map_parsing.c \
		mandatory/parsing/parser.c mandatory/parsing/parsing_utils.c \
		mandatory/parsing/read_file.c
SRC_BONUS = bonus/cub3d.c bonus/get_start.c bonus/draw_pixels.c bonus/hooks.c \
		bonus/rotate.c bonus/texture_handling.c bonus/player_movement.c \
		bonus/wall_checker.c bonus/moves_utils.c \
		bonus/ray_casting.c bonus/rays_utils.c bonus/open_door.c \
		bonus/horizontal.c bonus/vertical.c bonus/horizontal_utils.c bonus/vertical_utils.c \
		bonus/key_hooks.c bonus/parsing/general_utils.c bonus/parsing/map_parsing.c \
		bonus/parsing/parser.c bonus/parsing/parsing_utils.c \
		bonus/parsing/read_file.c bonus/parsing/parse_textures.c\
		bonus/sprites.c bonus/weapons.c bonus/door.c bonus/mem_free.c
CC = cc
MLX1 = minilibx/libmlx_Linux.a -lXext -lX11 -lm
LIBFT = libft/libft.a
HEADERS = bonus/graphics.h bonus/cub3d.h
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_OBJ = $(shell cat libft/Makefile | grep "ft_" | tr -d '\\' | tr -d "\n" \
			| tr "\t" " " |tr -s ' ' | sed 's/ / libft\//g' | sed 's/\.c/\.o/g')

$(NAME): libft $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX1) -o $(NAME)

$(BONUS): libft $(OBJ_BONUS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX1) -o $(BONUS)

libft: $(LIBFT_OBJ)
		make bonus -C libft/

all: $(NAME)

test:
	$(CC) $(CFLAGS) $(TEST) $(MLX1)

move:
	rm a.out

bonus: $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS) && make clean -C libft

fclean: clean
	rm -f $(NAME) $(BONUS) && make fclean -C libft

re: fclean all
