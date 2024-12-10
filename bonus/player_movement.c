/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/10 15:14:33 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	w_moves(t_data *data, float *tab)
{
	double	speed;

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
				tab[DELTA_Y] = 0;
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				tab[DELTA_X] = 0;
			else
			{
				tab[DELTA_X] = 0.0;
				tab[DELTA_Y] = 0.0;
				return ;
			}
		}
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
				tab[DELTA_Y] = 0;
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				tab[DELTA_X] = 0;
			else
			{
				tab[DELTA_X] = 0.0;
				tab[DELTA_Y] = 0.0;
				return ;
			}
		}
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
				tab[DELTA_Y] = 0;
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				tab[DELTA_X] = 0;
			else
			{
				tab[DELTA_X] = 0.0;
				tab[DELTA_Y] = 0.0;
				return ;
			}
		}
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
				tab[DELTA_Y] = 0;
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				tab[DELTA_X] = 0;
			else
			{
				tab[DELTA_X] = 0.0;
				tab[DELTA_Y] = 0.0;
				return ;
			}
		}
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
	data->player.player_x += tab[0];
	data->player.player_y += tab[1];
	data->player.mini_x = data->player.player_x
		* data->scale - (data->mini_width / 2);
	data->player.mini_y = data->player.player_y
		* data->scale - (data->mini_height / 2);
}
