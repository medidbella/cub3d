/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:24:00 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/16 14:01:06 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_coords(t_data *data, float delta_x, float delta_y)
{
	data->player.player_x += delta_x;
	data->player.player_y += delta_y;
	data->player.mini_x = data->player.player_x
		* data->scale - (data->mini_width / 2);
	data->player.mini_y = data->player.player_y
		* data->scale - (data->mini_height / 2);
	data->keys[MOVE_FLAG] = 1;
}

bool	wall_char(t_data *data, int y, int x)
{
	return (data->map[y][x] == '1');
}

bool	check_corners(t_data *data, int index_x, int index_y, int px)
{
	int	py;

	px = (data->player.player_x / TILE_SIZE);
	py = (data->player.player_y / TILE_SIZE);
	if (px > index_x && py > index_y)
	{
		if (wall_char(data, py, (px - 1)) && wall_char(data, py, (px - 1)))
			return (true);
	}
	else if (px < index_x && py < index_y)
	{
		if (wall_char(data, py, (px + 1)) && wall_char(data, (py + 1), px))
			return (true);
	}
	else if (px > index_x && py < index_y)
	{
		if (wall_char(data, py, (px - 1)) && wall_char(data, (py + 1), px))
			return (true);
	}
	else if (px < index_x && py > index_y)
	{
		if (wall_char(data, py, (px + 1)) && wall_char(data, (py - 1), px))
			return (true);
	}
	return (data->in_door = 0, false);
}

bool	check_barriers(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	float	index_x;
	float	index_y;

	new_x = data->player.player_x + x;
	new_y = data->player.player_y + y;
	if (data->player.player_y < new_y)
		new_y += data->speed;
	if (data->player.player_x < new_x)
		new_x += data->speed;
	index_x = (new_x / TILE_SIZE)
		- ((int)new_x % TILE_SIZE == 0 && data->player.player_x > new_x);
	index_y = (new_y / TILE_SIZE)
		- ((int)new_y % TILE_SIZE == 0 && data->player.player_y > new_y);
	if (!((int)index_y < data->height_2d
			&& (int)index_y >= 0 && (int)index_x >= 0
			&& (int)index_x < (int)ft_strlen(data->map[(int)index_y])))
		return (1);
	if (!ft_strchr("NSEW0HVhv", data->map[(int)index_y][(int)index_x]))
		return (1);
	if (ft_strchr("HV", data->map[(int)index_y][(int)index_x]))
		return (!next_to_door(data, new_x, new_y
				, data->map[(int)index_y][(int)index_x]));
	return (check_corners(data, (int)index_x, (int)index_y, 0));
}
