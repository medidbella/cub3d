/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:35:57 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/12 19:28:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(t_data *data, double x, double y)
{
	return (sqrt(pow((data->player.player_x - x), 2)
			+ pow((data->player.player_y - y), 2)));
}

void	init_vars(t_data *data, t_ray *ray, int *checks, int which)
{
	if (which == H_VARS)
	{
		ray->horizontal_y = data->player.player_y;
		ray->horizontal_x = data->player.player_x;
		ray->horizontal_distance = -1.0;
		ray->horizontal_door_flag = 0;
	}
	else
	{
		ray->vertical_y = data->player.player_y;
		ray->vertical_x = data->player.player_x;
		ray->vertical_distance = -1.0;
		ray->vertical_door_flag = 0;
	}
	*checks = 0;
}

void	initialize_vars(t_data *data, t_ray *ray, int *column)
{
	ray = &(data->ray);
	*column = 0;
	ray->rayangle = data->player.angle - (data->player.fov / 2);
	if (ray->rayangle < 0)
		ray->rayangle += radian(360);
	data->ray.hit_h_openedoor = 0;
	data->ray.hit_v_openedoor = 0;
	ray->direction_ray_distance = 0.0;
	ray->closest_hv = 0;
	ray->direction_flag = 0;
}

void	get_direction_coords(t_data *data)
{
	if (!data->ray.door)
	{
		data->ray.direction_door = 0;
		return ;
	}
	if (data->ray.side_flag == 1)
	{
		data->ray.direction_px = data->ray.horizontal_x;
		data->ray.direction_py = data->ray.horizontal_y;
	}
	else
	{
		data->ray.direction_px = data->ray.vertical_x;
		data->ray.direction_py = data->ray.vertical_y;
	}
	data->ray.direction_distance = data->ray.distance;
	data->ray.direction_door = data->ray.door;
}

void	direction_of_player(t_data *data)
{
	get_direction_coords(data);
}
