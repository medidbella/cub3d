/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:01:34 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	w_moves(t_data *data, float *tab)
{
	if (data->keys[W_FLAG])
	{
		tab[DELTA_X] = (cos(data->player.angle) * data->speed);
		tab[DELTA_Y] = (sin(data->player.angle) * data->speed);
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!tab[DELTA_X] || !tab[DELTA_Y])
				return (false);
			if (!check_barriers(data, tab[DELTA_X], 0.0))
				return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			else if (!check_barriers(data, 0, tab[DELTA_Y]))
				return (update_coords(data, 0.0, tab[DELTA_Y] * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

bool	s_moves(t_data *data, float *tab)
{
	if (data->keys[S_FLAG])
	{
		tab[DELTA_X] = (cos(data->player.angle) * data->speed) * -1;
		tab[DELTA_Y] = (sin(data->player.angle) * data->speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!tab[DELTA_X] || !tab[DELTA_Y])
				return (false);
			if (!check_barriers(data, tab[DELTA_X], 0.0))
				return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			else if (!check_barriers(data, 0.0, tab[DELTA_Y]))
				return (update_coords(data, 0.0, tab[DELTA_Y] * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

bool	d_moves(t_data *data, float *tab)
{
	if (data->keys[D_FLAG])
	{
		tab[DELTA_X] = (sin(data->player.angle) * data->speed) * -1;
		tab[DELTA_Y] = (cos(data->player.angle) * data->speed);
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!tab[DELTA_X] || !tab[DELTA_Y])
				return (false);
			if (!check_barriers(data, tab[DELTA_X], 0.0))
				return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			else if (!check_barriers(data, 0.0, tab[DELTA_Y]))
				return (update_coords(data, 0.0, tab[DELTA_Y] * 0.3), true);
			return (false);
		}
		return (update_coords(data, tab[DELTA_X], tab[DELTA_Y]), true);
	}
	return (false);
}

bool	a_moves(t_data *data, float *tab)
{
	if (data->keys[A_FLAG])
	{
		tab[DELTA_X] = (sin(data->player.angle) * data->speed);
		tab[DELTA_Y] = (cos(data->player.angle) * data->speed) * -1;
		if (tab[DELTA_Y] < 0.00001 && tab[DELTA_Y] > -0.00001)
			tab[DELTA_Y] = 0;
		if (tab[DELTA_X] < 0.00001 && tab[DELTA_X] > -0.00001)
			tab[DELTA_X] = 0;
		if (check_barriers(data, tab[DELTA_X], tab[DELTA_Y]))
		{
			if (!tab[DELTA_X] || !tab[DELTA_Y])
				return (false);
			if (!check_barriers(data, tab[DELTA_X], 0.0))
				return (update_coords(data, tab[DELTA_X] * 0.3, 0.0), true);
			else if (!check_barriers(data, 0.0, tab[DELTA_Y]))
				return (update_coords(data, 0.0, tab[DELTA_Y] * 0.3), true);
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
