/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:24:00 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/16 21:31:41 by alaktari         ###   ########.fr       */
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
	return (data->in_door = 0, data->in_h_door = 0, data->in_v_door = 0, false);
}

int	get_indexes(t_data *data, float *new_x, float *new_y, float *index_x)
{
	float	index_y;
	int		x_flag;
	int		y_flag;

	x_flag = 0;
	y_flag = 0;
	if (data->player.player_y < (*new_y) && !data->in_door && (int)(*new_y) % TILE_SIZE != 0)
	{
		(*new_y) += data->speed;
		y_flag = 1;
	}
	if (data->player.player_x < (*new_x) && !data->in_door && (int)(*new_x) % TILE_SIZE != 0)
	{
		(*new_x) += data->speed;
		x_flag = 1;
	}

	// printf("x flag: %d || y flag: %d\n", x_flag, y_flag);
	// printf("new x: %f || new y: %f\n", *new_x, *new_y);
	// printf("x flag: %d || y flag: %d\n", x_flag, y_flag);
	// exit(0);

	*index_x = ((*new_x) / TILE_SIZE)
		- ((int)(*new_x) % TILE_SIZE == 0 && ((data->player.player_x > (*new_x) && !data->in_v_door)
		|| (data->in_v_door && data->player.player_x < (*new_x))));
		
	index_y = ((*new_y) / TILE_SIZE)
		- ((int)(*new_y) % TILE_SIZE == 0 && ((data->player.player_y > (*new_y) && !data->in_h_door)
		|| (data->in_h_door && data->player.player_y < (*new_y))));

	// printf("char ==> %c\n", data->map[(int)index_y][(int)(*index_x)]);
	// exit(0);
		
	if (!(!((int)index_y < data->height_2d
			&& (int)index_y >= 0 && (int)(*index_x) >= 0
			&& (int)(*index_x) < (int)ft_strlen(data->map[(int)index_y]))))
	{
		if (ft_strchr("HV", data->map[(int)index_y][(int)(*index_x)]))
		{
			if (x_flag)
				*new_x -= data->speed;
			if (y_flag)
				*new_y -= data->speed;
	// printf("index x: %d || index y: %d\n", (int)(*index_x), (int)index_y);exit(0);
			if (!x_flag && !y_flag)
				return (index_y);
				
			*index_x = ((*new_x) / TILE_SIZE)
				- ((int)(*new_x) % TILE_SIZE == 0 && ((data->player.player_x > (*new_x))
				|| (data->in_v_door && data->player.player_x < (*new_x))));
				
			index_y = ((*new_y) / TILE_SIZE)
				- ((int)(*new_y) % TILE_SIZE == 0 && ((data->player.player_y > (*new_y))
				|| (data->in_h_door && data->player.player_y < (*new_y))));
		}
	}
	return (index_y);
	
}

bool	check_barriers(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	float	index_x;
	float	index_y;

	new_x = data->player.player_x + x;
	new_y = data->player.player_y + y;
	index_y = get_indexes(data, &new_x, &new_y, &index_x);
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
