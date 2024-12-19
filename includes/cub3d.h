/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:03:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:06:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# define TILE_SIZE 1000
# define MIN_TILE_SIZE 10
# define WIDTH 1080
# define HEIGHT 720

# define W 119
# define A 97
# define S 115
# define D 100
# define RIGHT 65363
# define LEFT 65361
# define UP 65362
# define DOWN 65364
# define CLOSE 65307
# define IMG_SIZE_X 4
# define IMG_SIZE_Y 4
# define ANGLE 1.5
# define WALL_COLOR 0x61F5B5
# define DIR_COLOR 0xFF0000
# define BLACK 0x000000
# define FOV 60
# define SPEED_DIVISOR 15
# define N_INDEX 0
# define S_INDEX 1
# define W_INDEX 2
# define E_INDEX 3

# define RIGHT_FLAG 0
# define LEFT_FLAG 1
# define W_FLAG 2
# define S_FLAG 3
# define D_FLAG 4
# define A_FLAG 5
# define CLOSE_FLAG 6
# define ROTATE_FLAG 7
# define MOVE_FLAG 8
# define KEYS_NB 9

typedef struct s_texture
{
	void	*img;
	char	*iter;
	int		line_lenght;
	int		pixel_bits;
	int		endianess;
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
	int		texture_idx;
	double	height;
}	t_ray;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	mini_x;
	double	mini_y;
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
	int			map_hight;
	int			map_width;
	double		scale;
	void		*mlx;
	void		*win;
	char		**map;
	int			width_2d;
	int			height_2d;
	int			mini_width;
	int			mini_height;
	t_img		img;
	t_img		img_2d;
	t_player	player;
	t_texture	wall_textures[4];
	int			ceiling_color;
	int			floor_color;
	int			keys[KEYS_NB];
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

void	free_textures_memory(void *mlx, t_texture *my_textures);
void	get_start(t_config *parsed_data);
void	init_key_flags(t_data *data);
int		ft_key_press(int key, t_data *data);
int		ft_key_release(int key, t_data *data);
int		loop_rendering(t_data *data);
int		close_win(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	radian(float degree);
void	rotate(t_data *data);
void	move_player(t_data *data);
void	a_moves(t_data *data);
void	d_moves(t_data *data);
void	s_moves(t_data *data);
void	w_moves(t_data *data);
void	ray_casting(t_data *data);
void	draw(t_data *data);
void	move_player(t_data *data);
void	my_mlx_pixel_put_2d(t_data *data, int x, int y, int color);
void	horizontal_distance(t_data *data, t_ray *ray, double rayangle);
double	get_distance(t_data *data, double x, double y);
void	vertical_distance(t_data *data, t_ray *ray, double rayangle);
void	get_texture_color(t_data *data, t_ray *ray, int current_y);
void	initialize_textures(t_data *data, t_config *parsed_data);
void	move_player(t_data *data);
bool	check_barriers(t_data *data, float x, float y);
#endif