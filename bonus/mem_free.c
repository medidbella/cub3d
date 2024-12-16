/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:31:39 by midbella          #+#    #+#             */
/*   Updated: 2024/12/16 16:38:14 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_sprites_memory(t_weapon *weapons, void *mlx)
{
	int	i;
	int	iter;

	i = 0;
	while (i < WEAPON_NB)
	{
		iter = 0;
		while (iter < weapons[i].frames_nb)
		{
			mlx_destroy_image(weapons[i].weapon_frames[iter].img, mlx);
			iter++;
		}
		i++;
	}
	free(weapons->weapon_frames);
}

void	free_wall_textures_memory(t_data *data, t_texture *my_textures)
{
	int	i;

	i = 0;
	while (i <= 3 + (data->door_flag == 1))
	{
		mlx_destroy_image(data->mlx, my_textures[i].img);
		i++;
	}
}

int	close_win(t_data *data)
{
	free_wall_textures_memory(data, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
