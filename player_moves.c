/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/15 18:24:49 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_barriers(t_data *data, float _x, float _y)
{
	int new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, new_x4, new_y4;

	new_x1 = data->player.player_x + _x;
	new_y1 = data->player.player_y + _y;
	
	new_x2 = data->player.player_x + 4 + _x;
	new_y2 = data->player.player_y + _y;

	new_x3 = data->player.player_x + _x;
	new_y3 = data->player.player_y + 4 + _y;

	new_x4 = data->player.player_x + 4 + _x;
	new_y4 = data->player.player_y + 4 + _y;
	
	if (get_color(data, new_x1, new_y1) || (get_color(data, new_x2, new_y2)) ||
	(get_color(data, new_x3, new_y3)) || get_color(data, new_x4, new_y4))
	return 1;
	
	return 0;
}

void w_s_moves(t_data *data, int key)
{
	double delta_x;
	double delta_y;
	
	delta_x = cos(radian(data->player.angle)) * ((double)DIRECTION / DEVIDE);
	delta_y = sin(radian(data->player.angle)) * ((double)DIRECTION / DEVIDE);
	// printf("\ndelta_x: %f || delta_y: %f\n", delta_x, delta_y);
	if (key == S)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_barriers(data, delta_x, delta_y))
		return ;
	draw_direction(data, BLACK);
	data->player.player_x += delta_x;
	data->player.player_y += delta_y;
	data->player.x_c += delta_x;
	data->player.y_c += delta_y;
	data->player.x_direction += delta_x;
	data->player.y_direction += delta_y;
}

void d_a_moves(t_data *data, int key)
{

	double	delta_x;
	double	delta_y;

	delta_x = sin(radian(data->player.angle)) * ((double)DIRECTION / DEVIDE);
	delta_y = cos(radian(data->player.angle)) * ((double)DIRECTION / DEVIDE);
	
	if (key == A)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_barriers(data, -delta_x, delta_y))
		return ;
	draw_direction(data, BLACK);
	data->player.player_x -= delta_x;
	data->player.player_y += delta_y;
	data->player.x_c -= delta_x;
	data->player.y_c += delta_y;
	data->player.x_direction -= delta_x;
	data->player.y_direction += delta_y;
	
}
