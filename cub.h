#ifndef CUB_H
#define CUB_h

#include "minilibx/mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "parsing_src/parsing.h"
#include <math.h>

#define ROWS 11
#define COLS 15
#define TILE_SIZE 25
#define WIDTH (COLS * TILE_SIZE) 
#define HEIGHT (ROWS * TILE_SIZE)

#define W 119
#define A 97
#define S 115
#define D 100
#define SPEED 2
#define IMG_SIZE_X 4
#define IMG_SIZE_Y 4


typedef struct s_player
{
	int		player;
	void	*player_img;
	void	*erase_img;
	int		player_x;
	int		player_y;
	int		x_c;
	int		y_c;
	int		size_x;
	int		size_y;
	int		mov_speed;
} t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct  s_data
{
    void		*mlx;
	void		*win;
    char		**map;
    t_img		img;
	t_player	player;
}   t_data;

void get_start(char **map);
int hooks(int key, t_data *data);
int	close_win1(t_data *data);

#endif