/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:01:23 by midbella          #+#    #+#             */
/*   Updated: 2024/12/18 19:01:22 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	sprites_init(t_weapon *weapons, void *mlx)
{
	int		i;
	int		iter;
	char	*tab[WEAPON_NB];

	i = -1;
	init_frames_number(weapons);
	tab[0] = ft_strdup("textures/pistole/pist_f1.xpm");
	tab[1] = ft_strdup("textures/machine_gun/mgun_f1.xpm");
	tab[2] = ft_strdup("textures/electric/electric_f1.xpm");
	tab[3] = ft_strdup("textures/shotgun/sgun_f1.xpm");
	while (++i < WEAPON_NB)
	{
		iter = -1;
		weapons[i].weapon_frames = malloc(sizeof(t_texture)
				* weapons[i].frames_nb);
		weapons[i].current_frame_index = 0;
		while (++iter < weapons[i].frames_nb)
		{
			texture_init(mlx, &weapons[i].weapon_frames[iter], tab[i]);
			tab[i][ft_strlen(tab[i]) - 5]++;
		}
		free(tab[i]);
	}
}

void	init_frame_render_data(t_weapon *weapon, int frame_index
								, int used_weapon)
{
	float	divider;

	divider = 3;
	if (used_weapon == PISTOLE)
		divider = 3.5;
	else if (used_weapon == MACHIN_GUN)
		divider = 2.3;
	weapon->scaled_width = WIDTH / divider;
	weapon->scaled_hight = HEIGHT / divider;
	weapon->x_scale = (float)weapon->weapon_frames[frame_index].width
		/ weapon->scaled_width;
	weapon->y_scale = (float)weapon->weapon_frames[frame_index].hight
		/ weapon->scaled_hight;
	weapon->x_start = WIDTH / 2 ;
}

void	start_animation(t_data	*data)
{
	if (data->weapons[data->used_weapon].current_frame_index != 0)
		return ;
	data->weapons[data->used_weapon].current_frame_index = 1;
	data->last_frame_time = ft_get_time();
}

void	set_frame_index(t_data *data)
{
	unsigned long	elapsed_time;

	if (data->weapons[data->used_weapon].current_frame_index == 0)
		return ;
	elapsed_time = ft_get_time() - data->last_frame_time;
	if (elapsed_time < FRAME_DELAY)
		return ;
	data->weapons[data->used_weapon].current_frame_index += 1;
	if (data->weapons[data->used_weapon].current_frame_index
		> data->weapons[data->used_weapon].frames_nb - 1)
		data->weapons[data->used_weapon].current_frame_index = 0;
	data->last_frame_time = ft_get_time();
}
