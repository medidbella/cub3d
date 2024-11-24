/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 12:40:13 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_data *data)
{
	if (!data->keys[0] && !data->keys[1])
		return ;
	if (data->keys[0])
	{
		data->player.angle += radian(ANGLE);
		if (data->player.angle >= radian(360))
			data->player.angle -= radian(360);
	}
	if (data->keys[1])
	{
		data->player.angle -= radian(ANGLE);
		if (data->player.angle < 0)
			data->player.angle = radian(355);
	}
}
