/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/19 16:49:04 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_values(t_data *data, t_ray *ray, t_draw_line *line)
{
	line->x1 = data->player.x_c;
	line->y1 = data->player.y_c;
	if (ray->side_flag == 1)
	{
		line->x2 = ray->horizontal_x;
		line->y2 = ray->horizontal_y;
	}
	else
	{
		line->x2 = ray->vertical_x;
		line->y2 = ray->vertical_y;
	}
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y1 < line->y2)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	bresenham(t_data *data, t_ray *ray)
{
	t_draw_line	line;

	init_values(data, ray, &line);
	while (1)
	{
		if (!get_color(data, line.x1, line.y1))
			my_mlx_pixel_put_2d(data, line.x1, line.y1, 0xFF0000);
		else
			break ;
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line.err2 = line.err * 2;
		if (line.err2 > -(line.dy))
		{
			line.err -= line.dy;
			line.x1 += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			line.y1 += line.sy;
		}
	}
}

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_data *data, int key)
{
	if (key == RIGHT)
	{
		data->player.angle += radian(ANGLE);
		if (data->player.angle >= radian(360))
			data->player.angle -= radian(360);
	}
	else
	{
		data->player.angle -= radian(ANGLE);
		if (data->player.angle < 0)
			data->player.angle = radian(355);
	}
}
