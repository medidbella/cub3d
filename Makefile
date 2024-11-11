NAME = cub
SRC = cub.c get_start.c hooks.c rotate.c player_moves.c ray_casting.c parsing/general_utils.c \
	parsing/map_parsing.c parsing/parser.c parsing/parsing_utils.c parsing/read_file.c
CC = cc
CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror 
MLX1 = -Lmlx_linux -lmlx_Linux -L minilibx -Imlx_linux -lXext -lX11 -lm -lz
MLX2 = -Imlx_linux
OBJ = $(SRC:.c=.o)
LIBFT_OBJ = $(shell cat libft/Makefile | grep "ft_" | tr -d '\\' | tr -d "\n" \
			| tr "\t" " " |tr -s ' ' | sed 's/ / libft\//g' | sed 's/\.c/\.o/g')

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a $(MLX1) -o $(NAME)

libft: $(LIBFT_OBJ)
		make bonus -C libft/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX2) -c $< -o $@

clean:
	rm -f $(OBJ) && make clean -C libft

fclean: clean
	rm -f $(NAME) && make fclean -C libft

re: fclean all