NAME = cub3d
BONUS = cub3d_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = mandatory_src/cub3d.c mandatory_src/get_start.c mandatory_src/hooks.c \
		mandatory_src/rotate.c mandatory_src/texture_handling.c mandatory_src/wall_checker.c\
		mandatory_src/player_movement.c mandatory_src/ray_casting.c \
		mandatory_src/horizontal.c mandatory_src/vertical.c mandatory_src/key_hooks.c \
		mandatory_src/parsing/general_utils.c mandatory_src/parsing/map_parsing.c \
		mandatory_src/parsing/parser.c mandatory_src/parsing/parsing_utils.c \
		mandatory_src/parsing/read_file.c
SRC_BONUS = bonus_src/cub3d.c bonus_src/get_start.c bonus_src/draw_pixels.c bonus_src/hooks.c \
		bonus_src/rotate.c bonus_src/texture_handling.c bonus_src/player_movement.c \
		bonus_src/wall_checker.c bonus_src/moves_utils.c \
		bonus_src/ray_casting.c bonus_src/rays_utils.c bonus_src/open_door.c bonus_src/door_utils.c\
		bonus_src/horizontal.c bonus_src/vertical.c bonus_src/horizontal_utils.c bonus_src/vertical_utils.c \
		bonus_src/key_hooks.c bonus_src/parsing/general_utils.c bonus_src/parsing/map_parsing.c \
		bonus_src/parsing/parser.c bonus_src/parsing/parsing_utils.c \
		bonus_src/parsing/read_file.c bonus_src/parsing/parse_textures.c\
		bonus_src/sprites.c bonus_src/weapons.c bonus_src/door.c bonus_src/mem_free.c\
		bonus_src/draw_fov.c bonus_src/wall_utils.c
CC = cc
MLX1 = -lmlx_Linux -lXext -lX11 -lm
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_OBJ = $(shell ls libft | grep ft_ | tr "\n" " " | sed 's/\.c/\.o/g' | sed 's/ft_/libft\/ft_/g')

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
