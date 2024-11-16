/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/15 15:38:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void bresenham(int x1, int y1, int x2, int y2, int color, t_data *data)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1; // step in x
    int sy = (y1 < y2) ? 1 : -1; // step in y
    int err = dx - dy; // error value

    while (1)
    {
		if (!get_color(data, x1, y1))
        	my_mlx_pixel_put_2d(data, x1, y1, color);
		else
			break;
        if (x1 == x2 && y1 == y2) break; // end point reached
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

float radian(float degree)
{
	return (degree * M_PI / 180);
}

float calculate_bc(t_data *data)
{
	return sqrt(pow(DIRECTION, 2) + pow(DIRECTION, 2) - (2 * DIRECTION * DIRECTION * cos(radian(data->player.angle))));
}


void rotate(t_data *data, int key)
{
	if (key == RIGHT)
		data->player.angle += ANGLE;
	else
	{
		if (data->player.angle == 0)
			data->player.angle = 360 - ANGLE;
		else
			data->player.angle -= ANGLE;
	}
	draw_direction(data, BLACK);
	if ((int)(data->player.angle) == 360)
	{
		
		data->player.x_direction = data->player.x_c + DIRECTION;
    	data->player.y_direction = data->player.y_c;
		data->player.angle = 0;
	}
	else
	{
		double delta_y = sin(radian(data->player.angle)) * DIRECTION;
		double delta_x = cos(radian(data->player.angle)) * DIRECTION;
		data->player.x_direction = data->player.x_c + delta_x;
		data->player.y_direction = data->player.y_c + delta_y;
	}
	// printf("angle player : %f\n", data->player.angle);
}
