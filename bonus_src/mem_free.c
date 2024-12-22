/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:31:39 by midbella          #+#    #+#             */
/*   Updated: 2024/12/22 13:24:03 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	while (i <= 3 + (data->door_flag == true))
	{
		mlx_destroy_image(data->mlx, my_textures[i].img);
		i++;
	}
}

void	free_sprites_textures_memory(void *mlx, t_weapon *weapons)
{
	int	i;
	int j;

	i = 0;
	while (i < WEAPON_NB)
	{
		j = 0;
		while (j < weapons[i].frames_nb)
			mlx_destroy_image(mlx, weapons[i].weapon_frames[j++].img);
		free(weapons[i].weapon_frames);
		i++;
	}
	
}


int	close_win(t_data *data)
{
	free_wall_textures_memory(data, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	free_sprites_textures_memory(data->mlx, data->weapons);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
