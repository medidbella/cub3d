/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:27:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/07 19:29:38 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	opening_possibility(t_data *data)
{
	if (data->ray.direction_door)
	{
		if (data->ray.direction_distance <= (TILE_SIZE * 2))
			return (true);
	}
	return (false);
}

void	open_door(t_data *data)
{
	int	index_x;
	int	index_y;

	if (!data->keys[OPEN_DOOR])
		return ;
	if (opening_possibility(data))
	{
		index_x = data->ray.direction_px / TILE_SIZE;
		index_y = data->ray.direction_py / TILE_SIZE;
		printf("--------------------------------------\n");
		printf("angle : %f\n" ,data->player.angle);
		printf("Px: %f || Py: %f\n", data->player.player_x, data->player.player_y);
		printf("\ndirection xd: %f || direction yd: %f\n", data->ray.direction_px, data->ray.direction_py);
		printf("dierction distance to door: %f\ndoor => %d\n\n", data->ray.direction_distance, data->ray.direction_door);
		printf("map[%d][%d] ==> %c\n", index_y, index_x, data->map[index_y][index_x]);
		printf("--------------------------------------\n");
		// exit(0);
		if (data->map[index_y][index_x] == 'H'
			|| data->map[index_y][index_x] == 'V')
			data->map[index_y][index_x] += 32;
		else
			data->keys[OPEN_DOOR] = 0;
	}
}
