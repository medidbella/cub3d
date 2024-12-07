/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:44:48 by midbella          #+#    #+#             */
/*   Updated: 2024/12/07 10:12:51 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	ft_get_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

void	init_frames_number(t_weapon *weapons)
{
	weapons[PISTOLE].frames_nb = PISTOLE_FNB;
	weapons[MACHIN_GUN].frames_nb = MACHINE_GUN_FNB;
	weapons[ELECTRIC_GUN].frames_nb = ELECTRIC_FNB;
	weapons[SHOTGUN].frames_nb = SHOTGUN_FNB;
}

void	weapon_switch(t_data *data, int flag)
{
	unsigned long	elapsed_time;

	if (data->weapons[data->used_weapon].current_frame_index != 0)
		return ;
	elapsed_time = ft_get_time() - data->last_weapon_switch_time;
	if (elapsed_time < CHANGE_DELAY)
		return ;
	data->used_weapon += flag;
	if (data->used_weapon == WEAPON_NB)
		data->used_weapon = 0;
	else if (data->used_weapon < 0)
		data->used_weapon = WEAPON_NB - 1;
	data->last_frame_time = ft_get_time();
	data->last_weapon_switch_time = ft_get_time();
}

void	render_weapon(t_data *data, t_weapon *weapon, int frame_index)
{
	unsigned int	color;
	int				x;
	int				y;

	init_frame_render_data(weapon, frame_index, data->used_weapon);
	x = 0;
	while (x < weapon->scaled_width)
	{
		y = 0;
		weapon->y_start = HEIGHT - weapon->scaled_hight;
		while (y < weapon->scaled_hight)
		{
			color = get_cords_color(&weapon->weapon_frames[frame_index],
					x * weapon->x_scale, y * weapon->y_scale);
			if (color != 0xff000000)
				my_mlx_pixel_put(data, weapon->x_start,
					weapon->y_start, color);
			weapon->y_start++;
			y++;
		}
		weapon->x_start++;
		x++;
	}
}
