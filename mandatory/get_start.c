/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/29 22:49:42 by alaktari         ###   ########.fr       */
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
				data->player.player_x = (x * TILE_SIZE + TILE_SIZE / 2)
					- (data->player.size_x / 2);
				data->player.player_y = (y * TILE_SIZE + TILE_SIZE / 2)
					- (data->player.size_y / 2);
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
	data->player.player_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/mini_player.xpm",
			&(data->player.size_x), &(data->player.size_y));
	data->player.erase_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/erase.xpm", &(data->player.size_x),
			&(data->player.size_y));
	data->scale = (float)MIN_TILE_SIZE / TILE_SIZE;
	player_first_coordinates(data);
	data->player.fov = radian(FOV);
	data->player.distance_to_project_plan = ((float)WIDTH / 2)
		/ tan(data->player.fov / 2);
}

static void	first_view(t_data *data)
{
	raplayer_yasting(data);
	draw(data);
	// draw_fov(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_player(data);
}

// int	mouse_hook(int button, int x, int y, t_data *data)
// {
// 	printf("addr ==> %p\n", data);
// 	printf("button: ==> %d || y: ==> %d || botton: ==> %d\n", button, x, y);
// 	printf("hello from mouse hook\n");
// 	return (0);
// }

int mouse_move_hook(int x, int y, t_data *data)
{
	y = y;
	if (data->keys[MOUSE_FLAG] == 0)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->keys[MOUSE_FLAG] = 1;
		return (0);
	}
	if (x > data->mouse_x)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->keys[R_MOUSE] = 1;
		data->player.angle += (double)ANGLE * 0.02;
		loop_rendering(data);
		data->keys[R_MOUSE] = 0;
	}
	else if (x < data->mouse_x)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->keys[L_MOUSE] = 1;
		data->player.angle -= (double)ANGLE * 0.02;
		loop_rendering(data);
		data->keys[L_MOUSE] = 0;
	}
	return (0);
}

void	get_start(t_config *parsed_data)
{
	t_data	data;

	printf("origine addr ==> %p\n", &data);
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
	// mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 6, 1L << 6, mouse_move_hook, &data);
	mlx_loop_hook(data.mlx, loop_rendering, &data);
	mlx_loop(data.mlx);
}
