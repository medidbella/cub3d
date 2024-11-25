/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:49:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/25 17:16:57 by alaktari         ###   ########.fr       */
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

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	// printf("color ==> x: %d || y: %d\n", x, y);
	if (x >= data->width_2d || y >= data->height_2d || x <= 0 || y <= 0)
		return (0);
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x
			* (data->img_2d.bits_per_pixel / 8));
	return (*(unsigned int *) dst == WALL_COLOR);
}

void	draw_cub(t_data *data, int x, int y)
{
	int	color;
	int	x_;
	int	y_;

	x_ = x;
	y_ = y;
	color = BLACK;
	if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		color = WALL_COLOR;
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
	int x;
	int y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSEW", data->map[y][x])
				&& data->player.player == 0)
			{
				data->player.player = 1;
				data->player.player_x = x * TILE_SIZE + TILE_SIZE / 2
					- (data->player.size_x / 2);
				data->player.player_y = y * TILE_SIZE + TILE_SIZE / 2
					- (data->player.size_y / 2);
			}
			draw_cub(data, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}
