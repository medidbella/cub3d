/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:09:48 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:01:34 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	get_char(t_data *data, int which)
{
	int	index_x;
	int	index_y;

	if (which == 1)
	{
		index_x = (int)data->player.player_x / TILE_SIZE;
		index_y = (int)data->player.player_y / TILE_SIZE;
	}
	else if (which == 2)
	{
		index_x = ((int)data->ray.vertical_x / TILE_SIZE)
			- (data->player.player_x > data->ray.vertical_x);
		index_y = (int)data->ray.vertical_y / TILE_SIZE;
	}
	else
	{
		index_x = (int)data->ray.horizontal_x / TILE_SIZE;
		index_y = ((int)data->ray.horizontal_y / TILE_SIZE)
			- (data->player.player_y > data->ray.horizontal_y);
	}
	return (data->map[index_y][index_x]);
}

static bool	player_in_door_cube_h(t_data *data, double rayangle,
			double *delta_y)
{
	int	half_cube;

	if (rayangle > radian(180))
	{
		if (get_char(data, 1) == 'H'
			&& (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_y / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_y = data->player.player_y - half_cube;
			return (data->ray.h_door = 1, true);
		}
	}
	else
	{
		if (get_char(data, 1) == 'H'
			&& (((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_y / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_y = data->player.player_y - half_cube;
			return (data->ray.h_door = 1, true);
		}
	}
	return (false);
}

static bool	ray_hits_door_h(t_data *data, double *delta_y)
{
	int	half_cube;

	if (data->player.player_y >= data->ray.horizontal_y)
	{
		if (get_char(data, 3) == 'H')
		{
			half_cube = (int)data->ray.horizontal_y - (TILE_SIZE / 2);
			*delta_y = data->ray.horizontal_y - half_cube;
			return (true);
		}
	}
	else
	{
		if (get_char(data, 3) == 'H')
		{
			half_cube = (int)data->ray.horizontal_y + (TILE_SIZE / 2);
			*delta_y = data->ray.horizontal_y - half_cube;
			return (true);
		}
	}
	return (false);
}

bool	h_ray_to_door(t_data *data, double rayangle, double *delta_y)
{
	if (!data->in_door && !data->ray.h_door)
		return (false);
	if (data->in_door && !data->ray.horizontal_door_flag)
		return (player_in_door_cube_h(data, rayangle, delta_y));
	else
		return (ray_hits_door_h(data, delta_y));
	return (false);
}
