/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:03:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/21 15:05:15 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "parsing/parsing.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define ROWS 9
# define COLS 25
# define TILE_SIZE 20
# define WIDTH 1280
# define HEIGHT 720

# define W 119
# define A 97
# define S 115
# define D 100
# define RIGHT 65363
# define LEFT 65361
# define UP 65362
# define DOWN 65364
# define CLOSE 32
# define IMG_SIZE_X 4
# define IMG_SIZE_Y 4
# define ANGLE 0.7
# define WALL_COLOR 0x61F5B5
# define DIR_COLOR 0xFF0000
# define BLACK 0x000000
# define FOV 60
# define SPEED 0.6
# define NORTH_CLR 0xF7AA3E
# define SOUTH_CLR 0x6EF48D
# define EAST_CLR 0x908CC5
# define WEST_CLR 0x5DBDFF

typedef struct s_texture
{
	void	*img;
	int		width;
	int		hight;
}	t_texture;

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
	double	height;
}	t_ray;

typedef struct s_player
{
	int		player;
	void	*player_img;
	void	*erase_img;
	double	player_x;
	double	player_y;
	double	x_c;
	double	y_c;
	int		size_x;
	int		size_y;
	int		mov_speed;
	double	angle;
	double	fov;
	double	angle_step;
	double	distance_to_project_plan;
	double	first_x_fov;
	double	last_x_fov;
	double	first_y_fov;
	double	last_y_fov;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width_2d;
	int			height_2d;
	t_img		img;
	t_img		img_2d;
	t_player	player;
	t_texture	wall_textures[4];
	int			ceiling_color;
	int			floor_color;
	int			keys[7];
}	t_data;

typedef struct s_draw
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;
}	t_draw;

typedef struct s_draw_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
	int	color;
}	t_draw_line;

void	get_start(t_config *parsed_data);
void	init_key_flags(t_data *data);
int		ft_key_press(int key, t_data *data);
int		ft_key_release(int key, t_data *data);
int		loop_rendering(t_data *data);
int		close_win(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_color(t_data *data, int x, int y);
float	radian(float degree);
void	rotate(t_data *data);
void	move_player(t_data *data);
void	a_moves(t_data *data);
void	d_moves(t_data *data);
void	s_moves(t_data *data);
void	w_moves(t_data *data);
void	bresenham(t_data *data, t_ray *ray);
void	ray_casting(t_data *data);
void	draw(t_data *data);
void	move_player(t_data *data);
void	my_mlx_pixel_put_2d(t_data *data, int x, int y, int color);
void	horizontal_distance(t_data *data, t_ray *ray, double rayangle);
double	get_distance(t_data *data, double x, double y);
void	vertical_distance(t_data *data, t_ray *ray, double rayangle);
void	draw_map2d(t_data *data);

void	fov_coordinates(t_data *data, t_ray *ray, int *first_fov, int which);
void	draw_fov(t_data *data, t_ray *ray);

#endif