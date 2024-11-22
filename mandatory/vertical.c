/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:49:47 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/21 14:43:53 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	calculate_delta_x(t_data *data, double *vertical_x
							, double *vertical_y, double rayangle)
{
	double	delta_x;

	if (rayangle > radian(90) && rayangle < radian(270))
	{
		if (*vertical_x == data->player.x_c && *vertical_y == data->player.y_c)
		{
			delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE))
					* TILE_SIZE);
			if (delta_x == 0)
				delta_x = TILE_SIZE;
		}
		else
			delta_x = TILE_SIZE;
	}
	else
	{
		if (*vertical_x == data->player.x_c && *vertical_y == data->player.y_c)
			delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE) + 1)
					* TILE_SIZE);
		else
			delta_x = -TILE_SIZE;
	}
	return (delta_x);
}

void	find_vertical_point(t_data *data, double rayangle, double *vertical_x
							, double *vertical_y)
{
	double	delta_x;
	double	delta_y;

	if (rayangle == radian(90) || rayangle == radian(270))
		return ;
	delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
	delta_y = tan(rayangle) * delta_x;
	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y - delta_y;
}

void	vertical_distance(t_data *data, t_ray *ray, double rayangle)
{
	double	check_x;

	ray->vertical_y = data->player.y_c;
	ray->vertical_x = data->player.x_c;
	while (1)
	{
		find_vertical_point(data, rayangle, &ray->vertical_x, &ray->vertical_y);
		if (rayangle == radian(90) || rayangle == radian(270)
			|| ray->vertical_x < 0 || ray->vertical_x > data->width_2d
			|| ray->vertical_y < 0 || ray->vertical_y > data->height_2d)
		{
			ray->vertical_distance = -1.0;
			break ;
		}
		check_x = ray->vertical_x;
		if (rayangle > radian(90) && rayangle < radian(270))
			check_x -= 1;
		if (get_color(data, check_x, ray->vertical_y))
		{
			ray->vertical_distance = get_distance(data, ray->vertical_x,
					ray->vertical_y);
			break ;
		}
	}
}
