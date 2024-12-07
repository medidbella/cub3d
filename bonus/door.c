/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:24 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/07 17:26:28 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_door_distance_h(t_data *data, t_ray *ray, double rayangle)
{
	double	delta_x;
	double	delta_y;

	delta_y = (double)TILE_SIZE / 2;
	delta_x = fabs(delta_y / tan(rayangle));
	if (data->player.player_y < ray->horizontal_y)
		delta_y *= -1;
	if (data->player.player_x < ray->horizontal_x)
		delta_x *= -1;
	ray->hx_door = ray->horizontal_x - delta_x;
	ray->hy_door = ray->horizontal_y - delta_y;
	return (get_distance(data, ray->hx_door, ray->hy_door));
}

static double	get_door_distance_v(t_data *data, t_ray *ray, double rayangle)
{
	double	delta_x;
	double	delta_y;

	delta_x = (double)TILE_SIZE / 2;
	delta_y = fabs(tan(rayangle) * delta_x);
	if (data->player.player_x < ray->vertical_x)
		delta_x *= -1;
	if (data->player.player_y < ray->vertical_y)
		delta_y *= -1;
	ray->vx_door = ray->vertical_x - delta_x;
	ray->vy_door = ray->vertical_y - delta_y;
	return (get_distance(data, ray->vx_door, ray->vy_door));
}

void	horizontal_door(t_data *data, t_ray *ray, double rayangle)
{
	double	h_door_dst;

	if (ray->h_door)
	{
		h_door_dst = get_door_distance_h(data, ray, rayangle);
		if (ray->vertical_distance != -1)
		{
			if (ray->vertical_distance < h_door_dst)
			{
				ray->distance = ray->vertical_distance;
				ray->side_flag = 2;
				ray->door = ray->v_door;
				return ;
			}
		}
		ray->distance = h_door_dst;
		ray->horizontal_x = ray->hx_door;
		ray->horizontal_y = ray->hy_door;
		ray->door = 1;
		return ;
	}
}

void	vertical_door(t_data *data, t_ray *ray, double rayangle)
{
	double	v_door_dst;

	if (ray->v_door)
	{
		v_door_dst = get_door_distance_v(data, ray, rayangle);
		if (ray->horizontal_distance != -1)
		{
			if (ray->horizontal_distance < v_door_dst)
			{
				ray->distance = ray->horizontal_distance;
				ray->side_flag = 1;
				ray->door = ray->h_door;
				return ;
			}
		}
		ray->distance = v_door_dst;
		ray->vertical_x = ray->vx_door;
		ray->vertical_y = ray->vy_door;
		ray->door = 1;
		return ;
	}
}

void	get_door_distance(t_data *data, t_ray *ray, double rayangle)
{
	if (ray->side_flag == 1)
		horizontal_door(data, ray, rayangle);
	else
		vertical_door(data, ray, rayangle);
}
