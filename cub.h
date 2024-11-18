#ifndef CUB_H
#define CUB_h

#include "parsing/parsing.h"
#include "minilibx/mlx.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 7
#define COLS 7
#define TILE_SIZE 20
#define WIDTH 1080
#define HEIGHT 720
#define WIDTH_2D (COLS * TILE_SIZE) 
#define HEIGHT_2D (ROWS * TILE_SIZE)

#define W 119
#define A 97
#define S 115
#define D 100
#define RIGHT 65363
#define LEFT 65361
#define UP 65362
#define DOWN 65364
#define CLOSE 32
#define IMG_SIZE_X 4
#define IMG_SIZE_Y 4
#define ANGLE 5
#define DIRECTION 15
#define WALL_COLOR 0x61F5B5
#define DIR_COLOR 0xFF0000
#define BLACK 0x000000
#define FOV 60
#define DEVIDE 5

#define NORTH_CLR 0xF7AA3E
#define SOUTH_CLR 0x6EF48D
#define EAST_CLR 0x908CC5
#define WEST_CLR 0x5DBDFF


typedef struct s_ray
{
	double	colums;
	double	distance;
	double	rayangle;
	double	raystep;
	double	horizontal_x;
	double	horizontal_y;
	double	horizontal_distance;
	double	vertical_x;
	double	vertical_y;
	double	vertical_distance;
	int		side_flag;

	int		curr_color;
	double	tall;

}	t_ray;

typedef struct s_player
{
	int		player;
	void	*player_img;
	void	*erase_img;
	double		player_x;
	double		player_y;
	double		x_c;
	double		y_c;
	int		size_x;
	int		size_y;
	int		mov_speed;

	double		x_direction;
	double		y_direction;
	double		angle;

	double		fov;
	double		angle_step; // the angle between each ray
	double		distance_to_project_plan;

	double		Projection_plane_distance;

	double	first_x_fov;
	double	last_x_fov;
	double	first_y_fov;
	double	last_y_fov;

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
	t_img		img_2d;
	t_player	player;
}   t_data;

void get_start(char **map, int start_angle);
int hooks(int key, t_data *data);
int	close_win1(t_data *data);
void rotate(t_data *data, int key);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int  get_color(t_data *data, int x, int y);
float radian(float degree);
float calculate_bc(t_data *data);
void draw_direction(t_data *data, int color);
void rotate(t_data *data, int key);
void w_s_moves(t_data *data, int key);
void bresenham(int x1, int y1, int x2, int y2, int color, t_data *data);
void DDA(int X0, int Y0, int X1, int Y1, int color, t_data *data);
void d_a_moves(t_data *data, int key);
void ray_casting(t_data *data);

void draw(t_data *data);

void move_player(t_data *data, int key);
void	my_mlx_pixel_put_2d(t_data *data, int x, int y, int color);

#endif