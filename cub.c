/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:33:15 by midbella          #+#    #+#             */
/*   Updated: 2024/11/14 13:55:03 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_config scene_data;

	if (ac != 2)
		return (write(2, "Error\nusage : ./cub3d (map_in_format.cub)\n", 42), 1);
	file_parser(&scene_data, av[1]);
	get_start(scene_data.map, scene_data.player_start_angle);
}