/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:49:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/13 17:04:38 by alaktari         ###   ########.fr       */
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

static void	fill_mini_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->mini_height)
	{
		x = 0;
		while (x <= data->mini_width)
		{
			my_mlx_pixel_put(data, x, y, 0xDCDCDC);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	int		player_center_x;
	int		player_center_y;
	// t_draw	draw;

	// draw.i = -2;
	player_center_x = (data->mini_width / 2) - (data->player.size_x / 2);
	player_center_y = (data->mini_height / 2) - (data->player.size_y / 2);
	// while (draw.i <= 2)
	// {
	// 	draw.j = -2;
	// 	while (draw.j <= 2)
	// 	{
	// 		draw.draw_x = player_center_x + draw.j;
	// 		draw.draw_y = player_center_y + draw.i;
	// 		if (draw.draw_x >= 0 && draw.draw_x < data->mini_width
	// 			&& draw.draw_y >= 0 && draw.draw_y < data->mini_height)
				mlx_put_image_to_window(data->mlx, data->win,
					data->player.player_img, player_center_x, player_center_y);
	// 		draw.j++;
	// 	}
	// 	draw.i++;
	// }
}

static void	draw_cub(t_data *data, int x, int y, int color)
{
	int		x_offset;
	int		y_offset;
	t_draw	draw;

	draw.i = 0;
	x_offset = x * MIN_TILE_SIZE - data->player.mini_x;
	y_offset = y * MIN_TILE_SIZE - data->player.mini_y;
	while (draw.i < MIN_TILE_SIZE)
	{
		draw.j = 0;
		while (draw.j < MIN_TILE_SIZE)
		{
			draw.draw_x = x_offset + draw.j;
			draw.draw_y = y_offset + draw.i;
			if (draw.draw_x >= 0 && draw.draw_x < data->mini_width
				&& draw.draw_y >= 0 && draw.draw_y < data->mini_height)
				my_mlx_pixel_put(data, draw.draw_x, draw.draw_y, color);
			draw.j++;
		}
		draw.i++;
	}
}

void	draw_mini_map(t_data *data)
{
	int	i;
	int	j;
	int	color;

	fill_mini_map(data);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			color = 0xFFFFFF;
			if (data->map[i][j] == '1')
				color = WALL_COLOR;
			else if (data->map[i][j] == '0'
			|| ft_strchr("NSEWhv", data->map[i][j]))
				color = BLACK;
			draw_cub(data, j, i, color);
		}
	}
	draw_fov(data);
}
