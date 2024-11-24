/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:04:34 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 17:19:58 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this file is just a temp file and it will be deteted
#include "cub3d.h"

void	draw_fov(t_data *data, t_ray *ray)
{
	bresenham(data, ray);
}

void	fov_coordinates(t_data *data, t_ray *ray, int *first_fov, int which)
{
	*first_fov = 1;
	if (ray->side_flag == 1)
	{
		if (which == 1)
		{
			data->player.first_x_fov = ray->horizontal_x;
			data->player.first_y_fov = ray->horizontal_y;
		}
		else
		{
			data->player.last_x_fov = ray->horizontal_x;
			data->player.last_y_fov = ray->horizontal_y;
		}
		return ;
	}
	if (which == 1)
	{
		data->player.first_x_fov = ray->vertical_x;
		data->player.first_x_fov = ray->vertical_y;
	}
	else
	{
		data->player.last_x_fov = ray->vertical_x;
		data->player.last_y_fov = ray->vertical_y;
	}
}
