/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:49:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/21 12:12:05 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= data->width_2d || y >= data->height_2d || x <= 0 || y <= 0)
		return (0);
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x
			* (data->img_2d.bits_per_pixel / 8));
	return (*(unsigned int *) dst == WALL_COLOR);
}

void	draw_cub(t_data *data, int x, int y, int color)
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
			else if (data->map[draw.i][draw.j] == '0')
				draw.color = BLACK;
			if (ft_strchr("NSEW", data->map[draw.i][draw.j])
			&& data->player.player == 0)
			{
				data->player.player = 1;
				data->player.player_x = draw.j * TILE_SIZE + TILE_SIZE / 2
					- (data->player.size_x / 2);
				data->player.player_y = draw.i * TILE_SIZE + TILE_SIZE / 2
					- (data->player.size_y / 2);
			}
			draw_cub(data, draw.x, draw.y, draw.color);
		}
	}
}
// lines 85 and 87 will be removed in mandatory part