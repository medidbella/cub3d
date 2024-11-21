NAME = cub
SRC = mandatory/cub.c mandatory/get_start.c mandatory/hooks.c mandatory/rotate.c mandatory/player_moves.c mandatory/ray_casting.c \
		mandatory/utils.c mandatory/horizontal.c mandatory/vertical.c mandatory/texture_handling.c \
	mandatory/parsing/general_utils.c mandatory/parsing/map_parsing.c mandatory/parsing/parser.c \
	mandatory/parsing/parsing_utils.c mandatory/parsing/read_file.c
CC = cc
CFLAGS = -fsanitize=address -g3 # -Wall -Wextra -Werror 
MLX1 = minilibx/libmlx_Linux.a -lXext -lX11 -lm
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
LIBFT_OBJ = $(shell cat libft/Makefile | grep "ft_" | tr -d '\\' | tr -d "\n" \
			| tr "\t" " " |tr -s ' ' | sed 's/ / libft\//g' | sed 's/\.c/\.o/g')

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX1) -o $(NAME)

libft: $(LIBFT_OBJ)
		make bonus -C libft/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) && make clean -C libft

fclean: clean
	rm -f $(NAME) && make fclean -C libft

re: fclean all