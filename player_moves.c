/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/16 23:01:40 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	w_s_moves(t_data *data, int key)
{
	double	delta_x;
	double	delta_y;

	delta_x = cos(data->player.angle) * ((double)DIRECTION / DEVIDE);
	delta_y = sin(data->player.angle) * ((double)DIRECTION / DEVIDE);
	if (key == S)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_barriers(data, delta_x, delta_y))
		return ;
	data->player.player_x += delta_x;
	data->player.player_y += delta_y;
	data->player.x_c += delta_x;
	data->player.y_c += delta_y;
}

void	d_a_moves(t_data *data, int key)
{
	double	delta_x;
	double	delta_y;

	delta_x = sin(data->player.angle) * ((double)DIRECTION / DEVIDE);
	delta_y = cos(data->player.angle) * ((double)DIRECTION / DEVIDE);
	if (key == A)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_barriers(data, -delta_x, delta_y))
		return ;
	data->player.player_x -= delta_x;
	data->player.player_y += delta_y;
	data->player.x_c -= delta_x;
	data->player.y_c += delta_y;
}
