/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:33:15 by midbella          #+#    #+#             */
/*   Updated: 2024/11/11 20:49:10 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_data data;
	t_config scene_data;

	if (ac != 2)
		return (write(2, "Error\nusage : ./cub3d (map_in_format.cub)\n", 42), 1);
	file_parser(&scene_data, av[1]);
	data.map = scene_data.map;
	data.player.player = 0;
    data.player.angle = scene_data.player_start_angle;
	setup(&data);
    printf("x_c : %d || y_c : %d\n", data.player.x_c, data.player.y_c);
    ray_casting(&data);
    draw_direction(&data, DIR_COLOR);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.player.player_img,
				data.player.player_x, data.player.player_y);
	mlx_hook(data.win, 2, 1L << 0, hooks, &data);
	mlx_hook(data.win, 17, 1L << 2, close_win1, &data);
	mlx_loop(data.mlx);
}
