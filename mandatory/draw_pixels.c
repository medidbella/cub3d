/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:49:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/27 19:31:14 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_2d(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= data->width_2d || y <= 0 || y >= data->height_2d)
		return ;
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x
			* (data->img_2d.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_cub(t_data *data, int x, int y, int color)
{
	int	x_;
	int	y_;

	x_ = x;
	y_ = y;
	while (y < y_ + TILE_SIZE)
	{
		x = x_;
		while (x < x_ + TILE_SIZE)
		{
			my_mlx_pixel_put_2d(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw(t_data *data)
{
	t_draw	draw;

	draw.i = -1;
	while (data->map[++(draw.i)])
	{
		draw.j = -1;
		draw.y = draw.i * TILE_SIZE;
		while (data->map[draw.i][++(draw.j)])
		{
			draw.color = BLACK;
			draw.x = draw.j * TILE_SIZE;
			if (data->map[draw.i][draw.j] == '1')
				draw.color = WALL_COLOR;
			draw_cub(data, draw.x, draw.y, draw.color);
		}
	}
}
