/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/19 16:49:28 by alaktari         ###   ########.fr       */
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

	if (x <= 0 || x >= WIDTH_2D || y <= 0 || y >= HEIGHT_2D)
		return ;
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x
			* (data->img_2d.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
				data->player.player_x = draw.j * TILE_SIZE  + TILE_SIZE / 2 - (data->player.size_x / 2);
				data->player.player_y = draw.i * TILE_SIZE + TILE_SIZE / 2 - (data->player.size_x / 2);
			}
			draw_cub(data, draw.x, draw.y, draw.color);
		}
	}
}

void	setup(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "none");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bits_per_pixel), &(data->img.line_length),
			&(data->img.endian));
	data->img_2d.img = mlx_new_image(data->mlx, WIDTH_2D, HEIGHT_2D);
	data->img_2d.addr = mlx_get_data_addr(data->img_2d.img,
			&(data->img_2d.bits_per_pixel),
			&(data->img_2d.line_length), &(data->img_2d.endian));
	data->player.player_img = mlx_xpm_file_to_image(data->mlx,
			"textures/mini_player.xpm",
			&(data->player.size_x), &(data->player.size_y));
	data->player.erase_img = mlx_xpm_file_to_image(data->mlx,
			"textures/erase.xpm", &(data->player.size_x),
			&(data->player.size_y));
	draw(data);
	data->player.x_c = data->player.player_x + (data->player.size_x / 2);
	data->player.y_c = data->player.player_y + (data->player.size_y / 2);
	data->player.fov = radian(FOV);
	data->player.angle_step = radian(((double)(FOV) / (double)WIDTH));
	data->player.distance_to_project_plan = ((float)WIDTH / 2)
		/ tan(data->player.fov / 2);
}

void	get_start(t_config *parsed_data)
{
	t_data	data;

	data.map = parsed_data->map;
	data.player.player = 0;
	data.ceiling_color = parsed_data->ceiling_color;
	data.floor_color = parsed_data->floor_color;
	data.player.angle = radian(parsed_data->player_start_angle);
	setup(&data);
	ray_casting(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.img_2d.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.player.player_img,
		data.player.player_x, data.player.player_y);
	mlx_hook(data.win, 2, 1L << 0, hooks, &data);
	mlx_hook(data.win, 17, 1L << 2, close_win1, &data);
	mlx_loop(data.mlx);
}
