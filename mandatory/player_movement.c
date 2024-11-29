/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/29 17:05:33 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_barriers(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	float	index_x;
	float	index_y;

	new_x = data->player.player_x + x;
	new_y = data->player.player_y + y;
	index_x = (new_x / TILE_SIZE)
		- ((int)new_x % TILE_SIZE == 0 && data->player.player_x > new_x);
	index_y = (new_y / TILE_SIZE)
		- ((int)new_y % TILE_SIZE == 0 && data->player.player_y > new_y);
	if (!((int)index_y < data->height_2d
			&& (int)index_y >= 0 && (int)index_x >= 0
			&& (int)index_x < (int)ft_strlen(data->map[(int)index_y])))
		return (1);
	if (!ft_strchr("NSEW0", data->map[(int)index_y][(int)index_x]))
		return (1);
	return (0);
}

void	w_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[2])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (cos(data->player.angle) * speed);
		delta_y = (sin(data->player.angle) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
	}
}

void	s_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[3])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (cos(data->player.angle) * speed) * -1;
		delta_y = (sin(data->player.angle) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
	}
}

void	d_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[4])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (sin(data->player.angle) * speed) * -1;
		delta_y = (cos(data->player.angle) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
	}
}

void	a_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[5])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (sin(data->player.angle) * speed);
		delta_y = (cos(data->player.angle) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
	}
}
