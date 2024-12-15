/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/15 23:05:06 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_first_coordinates(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.player_x = (x * TILE_SIZE + TILE_SIZE / 2);
				data->player.player_y = (y * TILE_SIZE + TILE_SIZE / 2);
				data->player.mini_x = data->player.player_x
					* data->scale - (data->mini_width / 2);
				data->player.mini_y = data->player.player_y
					* data->scale - (data->mini_height / 2);
				return ;
			}
		}
	}
}

static void	setup(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bits_per_pixel), &(data->img.line_length),
			&(data->img.endian));
	data->width_2d = (data->map_width * TILE_SIZE);
	data->height_2d = (data->map_hight * TILE_SIZE);
	data->mini_width = WIDTH / 6;
	data->mini_height = HEIGHT / 6;
	data->scale = (float)MIN_TILE_SIZE / TILE_SIZE;
	player_first_coordinates(data);
	data->player.fov = radian(FOV);
	data->player.distance_to_project_plan = ((float)WIDTH / 2)
		/ tan(data->player.fov / 2);
}

static void	first_view(t_data *data)
{
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	get_start(t_config *parsed_data)
{
	t_data	data;

	data.map = parsed_data->map;
	data.ceiling_color = parsed_data->ceiling_color;
	data.floor_color = parsed_data->floor_color;
	data.map_hight = parsed_data->map_hight;
	data.map_width = parsed_data->map_width;
	data.player.angle = radian(parsed_data->player_start_angle);
	data.player.angle_step = radian(((double)(FOV) / (double)WIDTH));
	setup(&data);
	initialize_textures(&data, parsed_data);
	parsed_data->map = NULL;
	free_parsed_data(parsed_data);
	init_key_flags(&data);
	first_view(&data);
	mlx_hook(data.win, 17, 1L << 2, close_win, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, ft_key_release, &data);
	mlx_loop_hook(data.mlx, loop_rendering, &data);
	mlx_loop(data.mlx);
}
