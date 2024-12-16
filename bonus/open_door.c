/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:27:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/16 14:38:06 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	closing_possibility(t_data *data, float distance1, float distance2,
			float distance)
{
	data->ray.closest_hv = 1;
	if (data->ray.hit_h_openedoor && !data->ray.hit_v_openedoor)
		distance = get_distance(data, data->ray.openedoor_hx,
				data->ray.openedoor_hy);
	else if (!data->ray.hit_h_openedoor && data->ray.hit_v_openedoor)
	{
		distance = get_distance(data, data->ray.openedoor_vx,
				data->ray.openedoor_vy);
		data->ray.closest_hv = 2;
	}
	else
	{
		distance1 = get_distance(data, data->ray.openedoor_hx,
				data->ray.openedoor_hy);
		distance2 = get_distance(data, data->ray.openedoor_vx,
				data->ray.openedoor_vy);
		distance = distance1;
		if (distance > distance2)
		{
			distance = distance2;
			data->ray.closest_hv = 2;
		}
	}
	return ((distance < data->ray.direction_ray_distance)
		&& (distance <= ((TILE_SIZE * 2) - (TILE_SIZE / 2))));
}

static void	opened_door(t_data *data)
{
	int	index_x;
	int	index_y;

	if (closing_possibility(data, 0.0, 0.0, 0.0))
	{
		if (data->ray.closest_hv == 1)
		{
			index_x = (data->ray.openedoor_hx / TILE_SIZE);
			index_y = (data->ray.openedoor_hy / TILE_SIZE)
				- (data->player.player_y > data->ray.openedoor_hy
					&& ((int)data->ray.openedoor_hy % TILE_SIZE == 0));
		}
		else
		{
			index_x = (data->ray.openedoor_vx / TILE_SIZE)
				- (data->player.player_x > data->ray.openedoor_vx
					&& ((int)data->ray.openedoor_vx % TILE_SIZE == 0));
			index_y = data->ray.openedoor_vy / TILE_SIZE;
		}
		if (data->map[index_y][index_x] == 'h'
			|| data->map[index_y][index_x] == 'v')
			data->map[index_y][index_x] -= 32;
		else
			data->keys[OPEN_DOOR] = 0;
	}
}

static bool	opening_possibility(t_data *data)
{
	if (data->ray.direction_door)
	{
		if (data->ray.direction_distance <= (TILE_SIZE * 2))
			return (true);
	}
	return (false);
}

static	void	close_or_open(t_data *data)
{
	int	index_x;
	int	index_y;

	if (opening_possibility(data))
	{
		index_x = data->ray.direction_px / TILE_SIZE;
		index_y = data->ray.direction_py / TILE_SIZE;
		if (data->map[index_y][index_x] == 'H'
			|| data->map[index_y][index_x] == 'V')
			data->map[index_y][index_x] += 32;
		else
			data->keys[OPEN_DOOR] = 0;
	}
}

void	open_and_close_door(t_data *data)
{
	if (!data->keys[OPEN_DOOR])
		return ;
	if (data->ray.hit_h_openedoor || data->ray.hit_v_openedoor)
		opened_door(data);
	else
		close_or_open(data);
}
