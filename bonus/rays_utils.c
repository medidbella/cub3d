/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:35:57 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/12 17:50:48 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
