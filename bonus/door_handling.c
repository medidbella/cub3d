/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:31:40 by midbella          #+#    #+#             */
/*   Updated: 2024/11/25 19:30:04 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_2d_wall(t_data *data, int x, int y)
{
	int	x_min;
	int	x_max;
	int	y_min;
	int	y_max;

	x_min = x + (TILE_SIZE / 3 * (data->map[y / TILE_SIZE]
			[x / TILE_SIZE] == 'V'));
	x_max = x + TILE_SIZE - (TILE_SIZE / 3 * data->map[y / TILE_SIZE]
		[x / TILE_SIZE] == 'V');
	y_min = y + (TILE_SIZE / 3 * (data->map[y / TILE_SIZE]
			[x / TILE_SIZE] == 'H'));
	y_max = y + TILE_SIZE - (TILE_SIZE / 3 * (data->map[y / TILE_SIZE]
			[x / TILE_SIZE] == 'H'));
	while (y_min <= y_max)
	{
		x = x_min;
		while (x <= x_max)
		{
			my_mlx_pixel_put_2d(data, x, y_min, DOOR_COLOR);
			x++;
		}
		y_min++;
	}
}
