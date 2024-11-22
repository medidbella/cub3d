/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:36 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/21 11:54:38 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	get_distance(t_data *data, double x, double y)
{
	return (sqrt(pow((data->player.x_c - x), 2)
			+ pow((data->player.y_c - y), 2)));
}

double	calculate_delta_y(t_data *data, double *horizontal_x
							, double *horizontal_y, double rayangle)
{
	double	delta_y;

	if (rayangle > radian(180))
	{
		if (*horizontal_x == data->player.x_c
			&& *horizontal_y == data->player.y_c)
		{
			delta_y = *horizontal_y
				- (((int)(*horizontal_y / TILE_SIZE)) * (TILE_SIZE));
			if (delta_y == 0)
				delta_y = TILE_SIZE;
		}
		else
			delta_y = TILE_SIZE;
	}
	else
	{
		if (*horizontal_x == data->player.x_c
			&& *horizontal_y == data->player.y_c)
			delta_y = (*horizontal_y)
				- (((int)((*horizontal_y) / TILE_SIZE) + 1) * TILE_SIZE);
		else
			delta_y = -TILE_SIZE;
	}
	return (delta_y);
}

void	find_horizontal_point(t_data *data, double rayangle
					, double *horizontal_x, double *horizontal_y)
{
	double	delta_x;
	double	delta_y;

	if (rayangle == 0 || rayangle == radian(180))
		return ;
	delta_y = calculate_delta_y(data, horizontal_x, horizontal_y, rayangle);
	delta_x = delta_y / tan(rayangle);
	*horizontal_x = *horizontal_x - delta_x;
	*horizontal_y = *horizontal_y - delta_y;
}

void	horizontal_distance(t_data *data, t_ray *ray, double rayangle)
{
	double	check_y;

	ray->horizontal_y = data->player.y_c;
	ray->horizontal_x = data->player.x_c;
	while (1)
	{
		find_horizontal_point(data, rayangle, &ray->horizontal_x,
			&ray->horizontal_y);
		if (rayangle == 0 || rayangle == radian(180)
			|| ray->horizontal_y > data->height_2d || ray->horizontal_y < 0
			|| ray->horizontal_x > data->width_2d || ray->horizontal_x < 0)
		{
			ray->horizontal_distance = -1.0;
			break ;
		}
		check_y = ray->horizontal_y;
		if (rayangle >= radian(180))
			check_y -= 1;
		if (get_color(data, ray->horizontal_x, check_y))
		{
			ray->horizontal_distance = get_distance(data, ray->horizontal_x,
					ray->horizontal_y);
			break ;
		}
	}
}
