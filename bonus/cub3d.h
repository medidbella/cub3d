/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:03:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/19 11:51:30 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/parsing.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
// # include <mlx.>"
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
# define CLOSE 65307
# define MOUSE_L_CLICK 65364
# define SCROLL_DOWNX 65364
# define DOWN 65364
# define OPEN 32

# define IMG_SIZE_X 4
# define IMG_SIZE_Y 4
# define ANGLE 1.5
# define FOV 60
# define SPEED_DIVISOR 10
# define FOV_LENGTH 20
# define FOV_COLOR	0xFF0000
# define WHITE 0xFFFFFF
# define BACKGROUND 0x989898

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
# define OPEN_DOOR 10
# define MOVE_FLAG 11
# define KEYS_NB 12
# define SENSITIVITY 0.2
# define DELTA_X 0
# define DELTA_Y 1
# define H_VARS 1
# define V_VARS 2

typedef struct s_ray
{
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
	int		player_side_flag;
	float	direction_px;
	float	direction_py;
	float	direction_distance;
	int		direction_door;
	int		curr_color;
	int		texture_idx;
	double	height;
	int		h_door;
	int		v_door;
	int		door;
	float	hx_door;
	float	hy_door;
	float	vx_door;
	float	vy_door;
	int		vertical_door_flag;
	int		horizontal_door_flag;
	int		hit_v_openedoor;
	int		hit_h_openedoor;
	float	openedoor_hx;
	float	openedoor_hy;
	float	openedoor_vx;
	float	openedoor_vy;
	int		direction_flag;
	float	direction_ray_distance;
	int		closest_hv;
}	t_ray;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	mini_x;
	double	mini_y;
	float	player_center_x;
	float	player_center_y;
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
	int				in_opendoor;
	int				in_h_door;
	int				in_v_door;
	t_ray			ray;
	float			speed;
	int				x_added;
	int				y_added;
}	t_data;

typedef struct s_draw
{
	int	i;
	int	j;
	int	draw_x;
	int	draw_y;
	int	color;
}	t_draw;

typedef struct s_draw_line
{
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		dx;
	int		dy;
	int		step;
	float	x_increment;
	float	y_increment;
	int		r;
	int		g;
	int		b;
	int		r_s;
	int		g_s;
	int		b_s;
	int		r_e;
	int		g_e;
	int		b_e;
	float	delta_r;
	float	delta_g;
	float	delta_b;
	int		steps;
	int		color;
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
void			bresenham(t_data *data, t_ray *ray);
void			ray_casting(t_data *data);
void			draw_mini_map(t_data *data);
void			move_player(t_data *data);
void			horizontal_distance(t_data *data, t_ray *ray);
double			get_distance(t_data *data, double x, double y);
void			vertical_distance(t_data *data, t_ray *ray);
void			get_texture_color(t_data *data, t_ray *ray, int current_y);
void			initialize_textures(t_data *data, t_config *parsed_data);
void			draw_2d_wall(t_data *data, int x, int y);
void			draw_player(t_data *data);
void			get_door_distance(t_data *data, t_ray *ray, double rayangle);
int				ft_mouse_press(int button, int x, int y, void *param);
int				ft_mouse_release(int button, int x, int y, void *param);
bool			h_ray_to_door(t_data *data, double rayangle, double *delta_y);
bool			v_ray_to_door(t_data *data, double rayangle, double *delta_x);
bool			next_to_door(t_data *data, float new_x, float new_y, char c);
void			direction_of_player(t_data *data);
void			open_and_close_door(t_data *data);
void			move_player(t_data *data);
bool			check_barriers(t_data *data, float x, float y);
char			get_char(t_data *data, int which);
bool			h_ray_to_door(t_data *data, double rayangle, double *delta_y);
bool			v_ray_to_door(t_data *data, double rayangle, double *delta_x);
void			init_vars(t_data *data, t_ray *ray, int *checks, int which);
void			initialize_vars(t_data *data, t_ray *ray, int *column);
void			draw_fov(t_data *data, float x2, float y2);
void			update_coords(t_data *data, float delta_x, float delta_y);
int				get_indexes(t_data *data, float *new_x, float *new_y,
					float *index_x);
bool			closing_possibility(t_data *data, float distance1,
					float distance2, float distance);
bool			opening_possibility(t_data *data);

#endif