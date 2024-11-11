/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/11 18:36:46 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_barriers(t_data *data, float _x, float _y)
{
	int new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, new_x4, new_y4;

	new_x1 = data->player.player_x + _x;
	new_y1 = data->player.player_y - _y;
	
	new_x2 = data->player.player_x + 4 + _x;
	new_y2 = data->player.player_y - _y;

	new_x3 = data->player.player_x + _x;
	new_y3 = data->player.player_y + 4 - _y;

	new_x4 = data->player.player_x + 4 + _x;
	new_y4 = data->player.player_y + 4 - _y;
	
	if (get_color(data, new_x1, new_y1) || (get_color(data, new_x2, new_y2)) ||
	(get_color(data, new_x3, new_y3)) || get_color(data, new_x4, new_y4))
	return 1;
	
	return 0;
}

void w_s_moves(t_data *data, int key)
{
    int _x;
	int _y;
	float beta = 90 - data->player.angle;
	_x = cos(radian(beta)) * DIRECTION / DEVIDE;
	_y = sin(radian(beta)) * DIRECTION / DEVIDE;
    if (key == S)
    {
        _y *= -1;
        _x *= -1;
    }
	if (check_barriers(data, _x, _y))
		return ;
	bresenham(data->player.x_c, data->player.y_c, data->player.x_direction2, data->player.y_direction2, 0x000000, data);
	data->player.player_y -= _y;
	data->player.player_x += _x;
	data->player.y_c -= _y;
	data->player.x_c += _x;
	data->player.y_direction2 -= _y;
	data->player.x_direction2 += _x;
	data->player.y_direction1 -= _y;
	data->player.x_direction1 += _x;
	bresenham(data->player.x_c, data->player.y_c, data->player.x_direction2, data->player.y_direction2, 0xFF0000, data);
}

void d_a_moves(t_data *data, int key)
{
	int _x;
	int _y;
	float beta;

	if (key == A)
	{
		beta = 90 - (90 - data->player.angle);
		_x = cos(radian(beta)) * DIRECTION / DEVIDE;
		_y = sin(radian(beta)) * DIRECTION / DEVIDE;
	}
	else
	{
		beta = 90 - data->player.angle;
		_x = sin(radian(beta)) * DIRECTION / DEVIDE * -1;
		_y = cos(radian(beta)) * DIRECTION / DEVIDE * -1;
	}

	if (check_barriers(data, -_x, _y))
		return ;

	// bresenham(data->player.x_c, data->player.y_c, data->player.x_direction2, data->player.y_direction2, 0x000000, data);
	draw_direction(data, BLACK);

	data->player.player_y -= _y;
	data->player.player_x -= _x;
	data->player.y_c -= _y;
	data->player.x_c -= _x;
	data->player.y_direction2 -= _y;
	data->player.x_direction2 -= _x;
	data->player.y_direction1 -= _y;
	data->player.x_direction1 -= _x;

	draw_direction(data, DIR_COLOR);
	// bresenham(data->player.x_c, data->player.y_c, data->player.x_direction2, data->player.y_direction2, 0xFF0000, data);

}