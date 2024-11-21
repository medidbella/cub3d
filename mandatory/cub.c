/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:33:15 by midbella          #+#    #+#             */
/*   Updated: 2024/11/21 14:00:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_start(t_data *data, t_config *parsed_data)
{
	data->map = parsed_data->map;
	data->player.player = 0;
	data->ceiling_color = parsed_data->ceiling_color;
	data->floor_color = parsed_data->floor_color;
	data->player.angle = radian(parsed_data->player_start_angle);
	data->mlx = mlx_init();
	initialize_textures(data, parsed_data);
	setup(data);
	first_view(data);
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release, data);
	mlx_loop_hook(data->mlx, loop_rendering, data);
	mlx_hook(data->win, 17, 1L << 2, close_win1, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_config	scene_data;

	if (ac != 2)
		return (write(2, "Error\nusage : ./cub3d (map_in_format.cub)\n", 42)
			, 1);
	file_parser(&scene_data, av[1]);
	get_start(&data, &scene_data);
}
