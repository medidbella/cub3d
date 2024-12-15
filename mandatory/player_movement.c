/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/14 17:39:15 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	move_player(t_data *data)
{
	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
// 	data->player.mini_x = data->player.player_x
// 		* data->scale - (data->mini_width / 2);
// 	data->player.mini_y = data->player.player_y
// 		* data->scale - (data->mini_height / 2);
}
