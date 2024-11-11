/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/09 16:04:43 by alaktari         ###   ########.fr       */
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
        	my_mlx_pixel_put(data, x1, y1, color);
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
				data->player.angle = 360 - 5;
			else
				data->player.angle -= ANGLE;
		}
		draw_direction(data, BLACK);
		if ((int)(data->player.angle) == 360)
		{
			data->player.x_direction2 = data->player.x_direction1;
			data->player.y_direction2 = data->player.y_direction1;
			data->player.angle = 0;
		}
		else
		{
			float beta = 90 - ((180 - data->player.angle) / 2);
			float bc = calculate_bc(data);
			float bo = cos(radian(beta)) * bc;
			float oc = sin(radian(beta)) * bc;
			data->player.x_direction2 = data->player.x_direction1 + bo;
			data->player.y_direction2 = data->player.y_direction1 + oc;
		}
	printf("angle player : %f\n", data->player.angle);
	draw_direction(data, DIR_COLOR);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
		data->player.player_x, data->player.player_y);
	// if (data->player.angle == 40)
	// 	ray_casting(data);
}
