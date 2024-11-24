/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 12:32:47 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_barriers(t_data *data, float x, float y)
{
	int	new_x;
	int	new_y;

	new_x = data->player.player_x + x;
	new_y = data->player.player_y + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + 4 + x;
	new_y = data->player.player_y + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + x;
	new_y = data->player.player_y + 4 + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + 4 + x;
	new_y = data->player.player_y + 4 + y;
	if (get_color(data, new_x, new_y))
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
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->player.x_c += delta_x;
		data->player.y_c += delta_y;
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
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->player.x_c += delta_x;
		data->player.y_c += delta_y;
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
		delta_x = (sin(data->player.angle) * speed);
		delta_y = (cos(data->player.angle) * speed);
		if (check_barriers(data, -delta_x, delta_y))
			return ;
		data->player.player_x -= delta_x;
		data->player.player_y += delta_y;
		data->player.x_c -= delta_x;
		data->player.y_c += delta_y;
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
		delta_x = (sin(data->player.angle) * speed) * -1;
		delta_y = (cos(data->player.angle) * speed) * -1;
		if (check_barriers(data, -delta_x, delta_y))
			return ;
		data->player.player_x -= delta_x;
		data->player.player_y += delta_y;
		data->player.x_c -= delta_x;
		data->player.y_c += delta_y;
	}
}
