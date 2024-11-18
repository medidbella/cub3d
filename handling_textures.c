/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:21:52 by midbella          #+#    #+#             */
/*   Updated: 2024/11/18 18:01:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_wall_textures(t_data *data, t_config *scene_data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(data->mlx,
			scene_data->textures_paths[i], data->wall_textures[i].width,
					data->wall_textures[i].hight);
			i++;
	}
}
