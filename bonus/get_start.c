/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 19:17:05 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put_mini(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= data->width_2d || y <= 0 || y >= data->height_2d)
		return ;
	dst = data->mini_map_img.addr + (y * data->mini_map_img.line_length + x
			* (data->mini_map_img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	setup(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bits_per_pixel), &(data->img.line_length),
			&(data->img.endian));
	data->width_2d = (data->map_width * TILE_SIZE);
	data->height_2d = (data->map_hight * TILE_SIZE);
	data->img_2d.img = mlx_new_image(data->mlx, data->width_2d,
			data->height_2d);
	data->img_2d.addr = mlx_get_data_addr(data->img_2d.img,
			&(data->img_2d.bits_per_pixel),
			&(data->img_2d.line_length), &(data->img_2d.endian));
	data->player.player_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/mini_player.xpm",
			&(data->player.size_x), &(data->player.size_y));
	data->player.erase_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/erase.xpm", &(data->player.size_x),
			&(data->player.size_y));
	draw(data);
	data->player.x_c = data->player.player_x + (data->player.size_x / 2);
	data->player.y_c = data->player.player_y + (data->player.size_y / 2);
	data->player.fov = radian(FOV);
	data->player.distance_to_project_plan = ((float)WIDTH / 2)
		/ tan(data->player.fov / 2);

	data->mini_map_img.img = mlx_new_image(data->mlx, MIN_MAP_WIDTH,
			MIN_MAP_HEIGHT);
	data->mini_map_img.addr = mlx_get_data_addr(data->mini_map_img.img,
			&(data->mini_map_img.bits_per_pixel),
			&(data->mini_map_img.line_length), &(data->mini_map_img.endian));
	int x = 0, y = 0;
	while (x < MIN_MAP_WIDTH)
	{
		y = 0;
		while (y < MIN_MAP_HEIGHT)
		{
			my_mlx_pixel_put_mini(data, x, y, 0xffffff);
			y++;
		}
		x++;
	}
}

void	first_view(t_data *data)
{
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
		data->player.player_x, data->player.player_y);
	// mlx_put_image_to_window(data->mlx, data->win, data->mini_map_img.img, 0, 0);
}

void	get_start(t_config *parsed_data)
{
	t_data	data;

	data.map = parsed_data->map;
	data.player.player = 0;
	data.ceiling_color = parsed_data->ceiling_color;
	data.floor_color = parsed_data->floor_color;
	data.map_hight = parsed_data->map_hight;
	data.map_width = parsed_data->map_width;
	data.player.angle = radian(parsed_data->player_start_angle);
	data.player.angle_step = radian(((double)(FOV) / (double)WIDTH));
	setup(&data);
	initialize_textures(&data, parsed_data);
	data.door_flag = parsed_data->door_flag;
	init_key_flags(&data);
	first_view(&data);
	mlx_hook(data.win, 17, 1L << 2, close_win, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, ft_key_release, &data);
	mlx_loop_hook(data.mlx, loop_rendering, &data);
	mlx_loop(data.mlx);
}
