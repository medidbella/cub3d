/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:33:15 by midbella          #+#    #+#             */
/*   Updated: 2024/12/02 21:46:33 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_config	scene_data;

	if (ac != 2)
		return (write(2, "Error\nusage : ./cub3d (map_in_format.cub)\n", 42)
			, 1);
	file_parser(&scene_data, av[1]);
	scene_data.map[2][5] = 'D';
	// scene_data.map[4][2] = 'D';
	// for (int i = 0; scene_data.map[i]; i++)
		// printf("[%s]\n", scene_data.map[i]);
	// exit(0);
	get_start(&scene_data);
}
