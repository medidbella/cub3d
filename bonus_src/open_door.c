/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:27:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/19 14:27:56 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	close_door(t_data *data, int *index_x, int *index_y)
{
	if (data->in_opendoor || closing_possibility(data, 0.0, 0.0, 0.0))
	{
		if (!data->in_opendoor && data->ray.closest_hv == 1)
		{
			if (!data->in_opendoor)
			{
				*index_x = (data->ray.openedoor_hx / TILE_SIZE);
				*index_y = (data->ray.openedoor_hy / TILE_SIZE)
					- (data->player.player_y > data->ray.openedoor_hy
						&& ((int)data->ray.openedoor_hy % TILE_SIZE == 0));
			}
		}
		else if (!data->in_opendoor)
		{
			*index_x = (data->ray.openedoor_vx / TILE_SIZE)
				- (data->player.player_x > data->ray.openedoor_vx
					&& ((int)data->ray.openedoor_vx % TILE_SIZE == 0));
			*index_y = data->ray.openedoor_vy / TILE_SIZE;
		}
		if (data->map[*index_y][*index_x] == 'h'
			|| data->map[*index_y][*index_x] == 'v')
			data->map[*index_y][*index_x] -= 32;
		else
			data->keys[OPEN_DOOR] = false;
	}
}

static	void	open_door(t_data *data)
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
			data->keys[OPEN_DOOR] = false;
	}
}

void	next_to_opendoor(t_data *data, int *index_x, int *index_y)
{
	*index_x = (int)data->player.player_x / TILE_SIZE;
	*index_y = (int)data->player.player_y / TILE_SIZE;
	data->in_opendoor = false;
	if (data->map[*index_y][*index_x] == 'h')
	{
		if (data->player.angle > 180
			&& (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2)))
			data->in_opendoor = true;
		else if (data->player.angle > 0 && data->player.angle < 180
			&& (((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2)))
			data->in_opendoor = true;
	}
	else if (data->map[*index_y][*index_x] == 'v')
	{
		if (data->player.angle > 90 && data->player.angle < 270
			&& (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2)))
			data->in_opendoor = true;
		else if ((data->player.angle > 270 || data->player.angle < 90)
			&& data->player.angle < 270
			&& (((int)data->player.player_y % TILE_SIZE)
				> (TILE_SIZE / 2)))
			data->in_opendoor = true;
	}
}

void	open_and_close_door(t_data *data)
{
	int	index_x;
	int	index_y;

	if (!data->keys[OPEN_DOOR])
		return ;
	next_to_opendoor(data, &index_x, &index_y);
	if (data->in_opendoor || data->ray.hit_h_openedoor
		|| data->ray.hit_v_openedoor)
		close_door(data, &index_x, &index_y);
	else
		open_door(data);
}
