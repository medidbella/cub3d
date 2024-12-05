/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:03:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/05 16:49:59 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/parsing.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "graphics.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>

# define TILE_SIZE 20
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
# define CLOSE 32
# define MOUSE_L_CLICK 65364
# define SCROLL_DOWNx 65364
# define DOWN 65364

# define IMG_SIZE_X 4
# define IMG_SIZE_Y 4
# define ANGLE 1.5
# define FOV 60
# define SPEED_DIVISOR 10

# define RIGHT_FLAG 0
# define LEFT_FLAG 1
# define W_FLAG 2
# define S_FLAG 3
# define D_FLAG 4
# define A_FLAG 5
# define CLOSE_FLAG 6
# define MOUSE_FLAG 7
# define SWITCH_FLAG 8
# define SHOOT_FLAG 9
# define KEYS_NB 10
# define SENSITIVITY 0.005

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
	int		h_door;
	int		v_door;
	int		door;
}	t_ray;

typedef struct s_player
{
	int		player;
	void	*player_img;
	void	*erase_img;
	double	player_x;
	double	player_y;
	double	mini_x;
	double	mini_y;
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
	int				map_hight;
	int				map_width;
	void			*mlx;
	void			*win;
	char			**map;
	int				width_2d;
	int				height_2d;
	int				mini_width;
	int				mini_height;
	double			scale;
	t_img			img;
	t_img			img_2d;
	t_player		player;
	t_texture		wall_textures[5];
	t_weapon		weapons[WEAPON_NB];
	int				ceiling_color;
	int				floor_color;
	int				door_flag;
	int				mouse_x;
	int				mouse_y;
	int				used_weapon;
	int				keys[KEYS_NB];
	unsigned long	last_frame_time;
	unsigned long	last_weapon_switch_time;
	int				in_door;
	int				debug;
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

void			get_start(t_config *parsed_data);
void			init_key_flags(t_data *data);
int				ft_key_press(int key, t_data *data);
int				ft_key_release(int key, t_data *data);
int				loop_rendering(t_data *data);
int				close_win(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned long	ft_get_time(void);
float			radian(float degree);
void			rotate(t_data *data);
void			move_player(t_data *data);
void			a_moves(t_data *data, float *tab);
void			d_moves(t_data *data, float *tab);
void			s_moves(t_data *data, float *tab);
void			w_moves(t_data *data, float *tab);
void			bresenham(t_data *data, t_ray *ray);
void			ray_casting(t_data *data);
void			draw(t_data *data);
void			move_player(t_data *data);
void			horizontal_distance(t_data *data, t_ray *ray, double rayangle);
double			get_distance(t_data *data, double x, double y);
void			vertical_distance(t_data *data, t_ray *ray, double rayangle);
void			get_texture_color(t_data *data, t_ray *ray, int current_y);
void			initialize_textures(t_data *data, t_config *parsed_data);
void			draw_2d_wall(t_data *data, int x, int y);
void			draw_player(t_data *data);
void			get_door_distance(t_data *data, t_ray *ray, double rayangle);
int				ft_mouse_press(int button, int x, int y, void *param);
int				ft_mouse_release(int button, int x, int y, void *param);
#endif