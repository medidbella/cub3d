/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:47:41 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/19 11:51:37 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	closing_possibility(t_data *data, float distance1, float distance2,
			float distance)
{
	data->ray.closest_hv = 1;
	if (data->ray.hit_h_openedoor && !data->ray.hit_v_openedoor)
		distance = get_distance(data, data->ray.openedoor_hx,
				data->ray.openedoor_hy);
	else if (!data->ray.hit_h_openedoor && data->ray.hit_v_openedoor)
	{
		distance = get_distance(data, data->ray.openedoor_vx,
				data->ray.openedoor_vy);
		data->ray.closest_hv = 2;
	}
	else
	{
		distance1 = get_distance(data, data->ray.openedoor_hx,
				data->ray.openedoor_hy);
		distance2 = get_distance(data, data->ray.openedoor_vx,
				data->ray.openedoor_vy);
		distance = distance1;
		if (distance > distance2)
		{
			distance = distance2;
			data->ray.closest_hv = 2;
		}
	}
	return ((distance < data->ray.direction_ray_distance)
		&& (distance <= ((TILE_SIZE * 2) - (TILE_SIZE / 2))));
}

bool	opening_possibility(t_data *data)
{
	if (data->ray.direction_door)
	{
		if (data->ray.direction_distance <= (TILE_SIZE * 2))
			return (true);
	}
	return (false);
}
