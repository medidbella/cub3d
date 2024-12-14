/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/14 17:36:48 by alaktari         ###   ########.fr       */
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
}

void	w_moves(t_data *data, float *tab)
{
	double	speed;
	data->debug = 1;

	if (data->keys[2])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (cos(data->player.angle) * speed);
		tab[DELTA_Y] = (sin(data->player.angle) * speed);
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!check_barriers(data, tab[DELTA_X], 0))
				update_coords(data, tab[DELTA_X] * 0.3, 0.0);
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				update_coords(data, 0.0, DELTA_Y * 0.3);
			return ;
		}
		update_coords(data, tab[DELTA_X], tab[DELTA_Y]);
	}
}

void	s_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[3])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (cos(data->player.angle) * speed) * -1;
		tab[DELTA_Y] = (sin(data->player.angle) * speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!check_barriers(data, tab[DELTA_X], 0))
				update_coords(data, tab[DELTA_X] * 0.3, 0.0);
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				update_coords(data, 0.0, DELTA_Y * 0.3);
			return ;
		}
		update_coords(data, tab[DELTA_X], tab[DELTA_Y]);
	}
}

void	d_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[4])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (sin(data->player.angle) * speed) * -1;
		tab[DELTA_Y] = (cos(data->player.angle) * speed);
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!check_barriers(data, tab[DELTA_X], 0))
				update_coords(data, tab[DELTA_X] * 0.3, 0.0);
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				update_coords(data, 0.0, DELTA_Y * 0.3);
			return ;
		}
		update_coords(data, tab[DELTA_X], tab[DELTA_Y]);
	}
}

void	a_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[5])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (sin(data->player.angle) * speed);
		tab[DELTA_Y] = (cos(data->player.angle) * speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!check_barriers(data, tab[DELTA_X], 0))
				update_coords(data, tab[DELTA_X] * 0.3, 0.0);
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				update_coords(data, 0.0, DELTA_Y * 0.3);
			return ;
		}
		update_coords(data, tab[DELTA_X], tab[DELTA_Y]);
	}
}

void	move_player(t_data *data)
{
	float	tab[2];

	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data, tab);
	s_moves(data, tab);
	d_moves(data, tab);
	a_moves(data, tab);
}
