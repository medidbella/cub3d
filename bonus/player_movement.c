/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/25 19:22:06 by alaktari         ###   ########.fr       */
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

void	w_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[2])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[0] = (cos(data->player.angle) * speed);
		tab[1] = (sin(data->player.angle) * speed);
		if (tab[1] < 0.00001 && tab[1] > -0.00001)
			tab[1] = 0;
		if (tab[0] < 0.00001 && tab[0] > -0.00001)
			tab[0] = 0;
		if (check_barriers(data, tab[0], tab[1]))
		{
			if (!check_barriers(data, tab[0], 0))
				tab[1] = 0;
			else if (!check_barriers(data, 0, tab[1]))
				tab[0] = 0;
			else
			{
				tab[0] = 0.0;
				tab[1] = 0.0;
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
		tab[0] = (cos(data->player.angle) * speed) * -1;
		tab[1] = (sin(data->player.angle) * speed) * -1;
		if (tab[1] < 0.00001 && tab[1] > -0.00001)
			tab[1] = 0;
		if (tab[0] < 0.00001 && tab[0] > -0.00001)
			tab[0] = 0;
		if (check_barriers(data, tab[0], tab[1]))
		{
			if (!check_barriers(data, tab[0], 0))
				tab[1] = 0;
			else if (!check_barriers(data, 0, tab[1]))
				tab[0] = 0;
			else
			{
				tab[0] = 0.0;
				tab[1] = 0.0;
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
		tab[0] = (sin(data->player.angle) * speed) * -1;
		tab[1] = (cos(data->player.angle) * speed);
		if (tab[1] < 0.00001 && tab[1] > -0.00001)
			tab[1] = 0;
		if (tab[0] < 0.00001 && tab[0] > -0.00001)
			tab[0] = 0;
		if (check_barriers(data, tab[0], tab[1]))
		{
			if (!check_barriers(data, tab[0], 0))
				tab[1] = 0;
			else if (!check_barriers(data, 0, tab[1]))
				tab[0] = 0;
			else
			{
				tab[0] = 0.0;
				tab[1] = 0.0;
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
		tab[0] = (sin(data->player.angle) * speed);
		tab[1] = (cos(data->player.angle) * speed) * -1;
		if (tab[1] < 0.00001 && tab[1] > -0.00001)
			tab[1] = 0;
		if (tab[0] < 0.00001 && tab[0] > -0.00001)
			tab[0] = 0;
		if (check_barriers(data, tab[0], tab[1]))
		{
			if (!check_barriers(data, tab[0], 0))
				tab[1] = 0;
			else if (!check_barriers(data, 0, tab[1]))
				tab[0] = 0;
			else
			{
				tab[0] = 0.0;
				tab[1] = 0.0;
				return ;
			}
		}
	}
}
