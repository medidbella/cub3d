/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:29:11 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:09 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_moves_up(t_data *data, float new_y)
{
	if (data->in_door)
	{
		if ((((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2))
			&& ((((int)new_y % TILE_SIZE) < (TILE_SIZE / 2))
				|| ((int)new_y % (TILE_SIZE / 2) == 0)))
			return (false);
		if (((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2))
			return (data->in_door = 1, data->in_h_door = 1, true);
	}
	if ((((int)new_y % TILE_SIZE) > (TILE_SIZE / 2))
		|| (((int)new_y % TILE_SIZE) == 0))
		return (data->in_door = 1, data->in_h_door = 1, true);
	return (false);
}

static bool	h_door(t_data *data, float new_y)
{
	if (data->player.player_y > new_y)
		return (player_moves_up(data, new_y));
	if (data->in_door == 1)
	{
		if ((((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2))
			&& ((((int)new_y % TILE_SIZE) > (TILE_SIZE / 2))
				|| ((int)new_y % (TILE_SIZE / 2) == 0)))
			return (false);
		if (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2))
			return (data->in_door = 1, data->in_h_door = 1, true);
	}
	if (((int)new_y % TILE_SIZE) < (TILE_SIZE / 2))
		return (data->in_door = 1, data->in_h_door = 1, true);
	return (false);
}

static	bool	player_moves_left(t_data *data, float new_x)
{
	if (data->in_door)
	{
		if ((((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2))
			&& ((((int)new_x % TILE_SIZE) < (TILE_SIZE / 2))
				|| ((int)new_x % (TILE_SIZE / 2) == 0)))
			return (false);
		if (((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2))
			return (data->in_door = 1, data->in_v_door = 1, true);
	}
	if ((((int)new_x % TILE_SIZE) > (TILE_SIZE / 2))
		|| (((int)new_x % TILE_SIZE) == 0))
		return (data->in_door = 1, data->in_v_door = 1, true);
	return (false);
}

static bool	v_door(t_data *data, float new_x)
{
	if (data->player.player_x > new_x)
		return (player_moves_left(data, new_x));
	if (data->in_door == 1)
	{
		if ((((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2))
			&& ((((int)new_x % TILE_SIZE) > (TILE_SIZE / 2))
				|| ((int)new_x % (TILE_SIZE / 2) == 0)))
			return (false);
		if (((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2))
			return (data->in_door = 1, data->in_v_door = 1, true);
	}
	if (((int)new_x % TILE_SIZE) < (TILE_SIZE / 2))
		return (data->in_door = 1, data->in_v_door = 1, true);
	return (false);
}

bool	next_to_door(t_data *data, float new_x, float new_y, char c)
{
	if (c == 'H')
		return (h_door(data, new_y));
	else if (c == 'V')
		return (v_door(data, new_x));
	return (data->in_door = 0, data->in_h_door = 0, data->in_v_door = 0, false);
}
