/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:06:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	w_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[W_FLAG])
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
		data->keys[MOVE_FLAG] = 1;
	}
}

void	s_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[S_FLAG])
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
		data->keys[MOVE_FLAG] = 1;
	}
}

void	d_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[D_FLAG])
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
		data->keys[MOVE_FLAG] = 1;
	}
}

void	a_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;
	double	speed;

	if (data->keys[A_FLAG])
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
		data->keys[MOVE_FLAG] = 1;
	}
}

void	move_player(t_data *data)
{
	if (!data->keys[W_FLAG] && !data->keys[S_FLAG] && !data->keys[D_FLAG]
		&& !data->keys[A_FLAG])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
}