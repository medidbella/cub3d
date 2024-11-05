NAME = cub
SRC = cub.c get_start.c hooks.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -fsanitize=address -g3#-Wall -Wextra -Werror 
MLX1 = -Lmlx_linux -lmlx_Linux -L minilibx -Imlx_linux -lXext -lX11 -lm -lz
MLX2 = -Imlx_linux

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX1) -o $(NAME)

	# $(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(MLX2) -c $< -o $@

	# $(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all