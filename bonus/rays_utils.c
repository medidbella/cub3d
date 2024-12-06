/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:35:57 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/06 16:16:15 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	get_char(t_data *data)
{
	int	index_x;
	int	index_y;

	index_x = (int)data->player.player_x / TILE_SIZE;
	index_y = (int)data->player.player_y / TILE_SIZE;
	return (data->map[index_y][index_x]);
}

bool	v_ray_to_door(t_data *data, double rayangle, double *delta_x)
{
	int		half_cube;

	if (data->in_door && (rayangle > radian(90) && rayangle < radian(270)))
	{
		if (get_char(data) == 'V'
			&& (((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_x / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_x = data->player.player_x - half_cube;
			return (true);
		}
	}
	else if (data->in_door)
	{
		if (get_char(data) == 'V'
			&& (((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_x / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_x = data->player.player_x - half_cube;
			return (true);
		}
	}
	return (false);
}

bool	h_ray_to_door(t_data *data, double rayangle, double *delta_y)
{
	int		half_cube;

	if (data->in_door && (rayangle > radian(180)))
	{
		if (get_char(data) == 'H'
			&& (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_y / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_y = data->player.player_y - half_cube;
			return (true);
		}
	}
	else if (data->in_door)
	{
		if (get_char(data) == 'H'
			&& (((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_y / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_y = data->player.player_y - half_cube;
			return (true);
		}
	}
	return (false);
}
