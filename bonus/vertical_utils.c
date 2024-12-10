/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:08:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/10 15:30:48 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_in_door_cube_v(t_data *data, double rayangle,
			double *delta_x)
{
	int	half_cube;

	if (rayangle > radian(90) && rayangle < radian(270))
	{
		if (get_char(data, 1) == 'V'
			&& (((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_x / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_x = data->player.player_x - half_cube;
			return (data->ray.v_door = 1, true);
		}
	}
	else
	{
		if (get_char(data, 1) == 'V'
			&& (((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2)))
		{
			half_cube = (((int)(data->player.player_x / TILE_SIZE))
					* (TILE_SIZE)) + (TILE_SIZE / 2);
			*delta_x = data->player.player_x - half_cube;
			return (data->ray.v_door = 1, true);
		}
	}
	return (false);
}

static bool	ray_hits_door_v(t_data *data, double *delta_x)
{
	int	half_cube;

	if (data->player.player_x >= data->ray.vertical_x)
	{
		if (get_char(data, 2) == 'V')
		{
			half_cube = (int)data->ray.vertical_x - (TILE_SIZE / 2);
			*delta_x = data->ray.vertical_x - half_cube;
			return (true);
		}
	}
	else
	{
		if (get_char(data, 2) == 'V')
		{
			half_cube = (int)data->ray.vertical_x + (TILE_SIZE / 2);
			*delta_x = data->ray.vertical_x - half_cube;
			return (true);
		}
	}
	return (false);
}

bool	v_ray_to_door(t_data *data, double rayangle, double *delta_x)
{
	if (!data->in_door && !data->ray.v_door)
		return (false);
	if (data->in_door && !data->ray.vertical_door_flag)
		return (player_in_door_cube_v(data, rayangle, delta_x));
	else
		return (ray_hits_door_v(data, delta_x));
	return (false);
}
