/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/27 19:21:43 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_barriers(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	float	index_x;
	float	index_y;

	new_x = data->player.x_c + x;
	new_y = data->player.y_c + y;
	index_x = (new_x / TILE_SIZE)
		- ((int)new_x % TILE_SIZE == 0 && data->player.x_c > new_x);
	index_y = (new_y / TILE_SIZE)
		- ((int)new_y % TILE_SIZE == 0 && data->player.y_c > new_y);
	if (!((int)index_y < data->height_2d
			&& (int)index_y >= 0 && (int)index_x >= 0
			&& (int)index_x < (int)ft_strlen(data->map[(int)index_y])))
		return (1);
	if (!ft_strchr("NSEW0", data->map[(int)index_y][(int)index_x]))
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
