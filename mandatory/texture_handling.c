/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:01:07 by midbella          #+#    #+#             */
/*   Updated: 2024/11/21 18:50:05 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int get_cords_color(t_texture *img, int x, int y)
{
	char *dst;

	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
	return (*(int*)dst);
}

int	get_texture_x_cord(int current_tile_x, int texture_width)
{
	float pixel_step;

	pixel_step = texture_width / TILE_SIZE;
	// printf("texture x index = %f\n", pixel_step * current_tile_x);
	return (pixel_step * current_tile_x);
}

int get_texture_y_cord(int current_tile_y, int texture_hight, int ray_len)
{
	float pixel_step;
	pixel_step = texture_hight / ray_len;
	// printf("texture y index = %f\n", pixel_step * current_tile_y);
	return (pixel_step * current_tile_y);
}

void	initialize_textures(t_data *data, t_config *parsed_data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(data->mlx,
			parsed_data->textures_paths[i], &data->wall_textures[i].width,
				&data->wall_textures[i].hight);
		data->wall_textures[i].iter = mlx_get_data_addr(data->wall_textures[i].img, &data->wall_textures[i].pixel_bits,
				&data->wall_textures[i].line_lenght,
					&data->wall_textures[i].endianess);
		i++;
	}
}

void	get_texture_color(t_data *data, t_ray *ray, int current_y)
{
	// static int i;
	int current_x;
	
	if (ray->texture_idx == N_INDEX)
		current_x = (int)ray->horizontal_x % TILE_SIZE;
	else if (ray->texture_idx == S_INDEX)
		current_x = TILE_SIZE - ((int)ray->horizontal_x % TILE_SIZE);
	else if (ray->texture_idx == E_INDEX)
		current_x = (int)ray->vertical_y % TILE_SIZE;
	else if (ray->texture_idx == W_INDEX)
		current_x = TILE_SIZE - ((int)ray->vertical_y % TILE_SIZE);
	// printf("x_len = %d\n", current_x);
	// printf("x_len = %d\n", current_y);
	// printf("side flag = %d\n", ray->texture_idx);
	ray->curr_color = get_cords_color(&data->wall_textures[ray->texture_idx],
		get_texture_x_cord(current_x, data->wall_textures[ray->texture_idx].width),
		get_texture_y_cord(current_y, data->wall_textures[ray->texture_idx].hight,
			ray->height));
	// i++;
	// printf("----------------------------------------------------\n");
	// if (i == 5)
		// exit(0);
}
