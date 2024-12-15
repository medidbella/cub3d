/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/15 13:10:56 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	w_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[W_FLAG])
	{
		// data->debug++;
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (cos(data->player.angle) * speed);
		tab[DELTA_Y] = (sin(data->player.angle) * speed);

		// printf("debug: %d\n", data->debug);
		// printf("delta X: %f || delta Y: %f\n", tab[DELTA_X], tab[DELTA_Y]);
		// exit(0);
		
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y], 1))
		{
			// if (!check_barriers(data, tab[DELTA_X], 0, 0))
			// 	return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			// else if (!check_barriers(data, 0, tab[DELTA_Y], 0))
			// 	return (update_coords(data, 0.0, DELTA_Y * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

bool	s_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[S_FLAG])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (cos(data->player.angle) * speed) * -1;
		tab[DELTA_Y] = (sin(data->player.angle) * speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y], 1))
		{
			// if (!check_barriers(data, tab[DELTA_X], 0.0, 0))
			// 	return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			// else if (!check_barriers(data, 0.0, tab[DELTA_Y], 0))
			// 	return (update_coords(data, 0.0, DELTA_Y * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

bool	d_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[D_FLAG])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (sin(data->player.angle) * speed) * -1;
		tab[DELTA_Y] = (cos(data->player.angle) * speed);
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y], 1))
		{
			// if (!check_barriers(data, tab[DELTA_X], 0.0, 0))
			// 	return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			// else if (!check_barriers(data, 0.0, tab[DELTA_Y], 0))
			// 	return (update_coords(data, 0.0, DELTA_Y * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}


bool	a_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[A_FLAG])
	{
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[DELTA_X] = (sin(data->player.angle) * speed);
		tab[DELTA_Y] = (cos(data->player.angle) * speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y], 1))
		{
			// if (!check_barriers(data, tab[DELTA_X], 0.0, 0))
			// 	return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			// else if (!check_barriers(data, 0.0, tab[DELTA_Y], 0))
			// 	return (update_coords(data, 0.0, DELTA_Y * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

void	move_player(t_data *data)
{
	float	tab[2];

	if (!data->keys[W_FLAG] && !data->keys[S_FLAG] && !data->keys[D_FLAG]
		&& !data->keys[A_FLAG])
		return ;
	w_moves(data, tab);
	s_moves(data, tab);
	d_moves(data, tab);
	a_moves(data, tab);
}
