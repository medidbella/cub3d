/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/06 11:57:30 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	next_to_door(t_data *data, float new_x, float new_y, char c)
{
	new_x = new_x;

	if (c == 'H')
	{
		if (data->player.player_y > new_y)
		{
			if (data->in_door)
			{
				if ((((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2))
					&& ((((int)new_y % TILE_SIZE) < (TILE_SIZE / 2)) || ((int)new_y % (TILE_SIZE / 2) == 0)))
					return (false);
				if (((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2))
					return (data->in_door = 1, true);
			}
			if ((((int)new_y % TILE_SIZE) > (TILE_SIZE / 2)) || (((int)new_y % TILE_SIZE) == 0))
				return (data->in_door = 1, true);
			return (false);
		}
		else
		{
			if (data->in_door == 1)
			{
				if ((((int)data->player.player_y % TILE_SIZE) < (TILE_SIZE / 2))
					&& ((((int)new_y % TILE_SIZE) > (TILE_SIZE / 2)) || ((int)new_y % (TILE_SIZE / 2) == 0)))
						return (false);
				if (((int)data->player.player_y % TILE_SIZE) > (TILE_SIZE / 2))
					return (data->in_door = 1, true);
			}
			if (((int)new_y % TILE_SIZE) < (TILE_SIZE / 2))
				return (data->in_door = 1, true);
			return (false);
		}
	}
	else if (c == 'V')
	{
		if (data->player.player_x > new_x)
		{
			if (data->in_door)
			{
				if ((((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2))
					&& ((((int)new_x % TILE_SIZE) < (TILE_SIZE / 2)) || ((int)new_x % (TILE_SIZE / 2) == 0)))
					return (false);
				if (((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2))
					return (data->in_door = 1, true);
			}
			if ((((int)new_x % TILE_SIZE) > (TILE_SIZE / 2)) || (((int)new_x % TILE_SIZE) == 0))
				return (data->in_door = 1, true);
			return (false);
		}
		else
		{
			if (data->in_door == 1)
			{
				if ((((int)data->player.player_x % TILE_SIZE) < (TILE_SIZE / 2))
					&& ((((int)new_x % TILE_SIZE) > (TILE_SIZE / 2)) || ((int)new_x % (TILE_SIZE / 2) == 0)))
						return (false);
				if (((int)data->player.player_x % TILE_SIZE) > (TILE_SIZE / 2))
					return (data->in_door = 1, true);
			}
			if (((int)new_x % TILE_SIZE) < (TILE_SIZE / 2))
				return (data->in_door = 1, true);
			return (false);
		}
	}
	return (data->in_door = 0, false);
}

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
	if (!ft_strchr("NSEW0HV", data->map[(int)index_y][(int)index_x]))
		return (1);
	if (ft_strchr("HV", data->map[(int)index_y][(int)index_x]))
	{
		// printf("new x: %f || new y: %f\n", new_x, new_y);
		return (!next_to_door(data, new_x, new_y, data->map[(int)index_y][(int)index_x]));
	}
	return (0);
}

void	w_moves(t_data *data, float *tab)
{
	double	speed;

	if (data->keys[2])
	{
		data->debug++;
		speed = (double)TILE_SIZE / SPEED_DIVISOR;
		tab[0] = (cos(data->player.angle) * speed);
		tab[1] = (sin(data->player.angle) * speed);
		if (tab[1] < 0.00001 && tab[1] > -0.00001)
			tab[1] = 0;
		if (tab[0] < 0.00001 && tab[0] > -0.00001)
			tab[0] = 0;
		// printf("new x: %f || new y: %f\n", data->player.player_x + tab[0], data->player.)
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
