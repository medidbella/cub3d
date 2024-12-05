/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:56:40 by midbella          #+#    #+#             */
/*   Updated: 2024/12/05 10:59:54 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# define PISTOLE 0
# define MACHIN_GUN 1
# define ELECTRIC_GUN 2

# define PISTOLE_FNB 5
# define MACHINE_GUN_FNB 4
# define ELECTRIC_FNB 11
# define WEAPON_NB 3
# define N_INDEX 0
# define S_INDEX 1
# define W_INDEX 2
# define E_INDEX 3
# define CHANGE_WEAPON 113
# define SHOOT_BUTTON 120
# define WALL_INDEX 4
# define WALL_COLOR 0x61F5B5
# define DOOR_COLOR 0xffc704
# define BLACK 0x000000
# define FRAME_DELAY 50 //milliseconds
# define CHANGE_DELAY 100
typedef struct s_ray t_ray;
typedef struct s_player t_player;
typedef struct s_data t_data;
typedef struct s_config t_config;

typedef struct s_texture
{
	void	*img;
	char	*iter;
	int		line_length;
	int		pixel_bits;
	int		endianess;
	int		width;
	int		hight;
}	t_texture;

typedef struct s_weapon
{
	t_texture	*weapon_frames;
	int			x_start;
	int			y_start;
	int			frames_nb;
	float		x_scale;
	float		y_scale;
	int			current_frame_index;
	int			scaled_width;
	int			scaled_hight;
}	t_weapon;

void	texture_init(void *mlx, t_texture *texture, char *file_path);
int		get_cords_color(t_texture *img, int x, int y);
void	free_wall_textures_memory(t_data *data, t_texture *my_textures);
void	get_texture_color(t_data *data, t_ray *ray, int current_y);
void	initialize_wall_textures(t_data *data, t_config *parsed_data);
void	sprites_init(t_weapon *weapons, void *mlx);
void	free_sprites_memory(t_weapon *weapons, void *mlx);
void	render_weapon(t_data *data, t_weapon *weapon, int frame_index);
void	weapon_switch(t_data *data, int flag);
void	start_animation(t_data *data);
void	set_frame_index(t_data *data);
void	init_frame_render_data(t_weapon *weapon, int frame_index, int used_weapon);

#endif