/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:01:07 by midbella          #+#    #+#             */
/*   Updated: 2024/11/21 14:02:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int get_cords_color(t_texture *img, int x, int y)
{
	char *dst;

	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
	return ((int)*dst);
}

int	get_texture_x_cord(int current_tile_x, int texture_width)
{
	float pixel_step;

	pixel_step = texture_width / TILE_SIZE;
	return (pixel_step * current_tile_x);
}

int get_texture_y_cord(int current_tile_y, int texture_hight, int ray_len)
{
	float pixel_step;
	pixel_step = texture_hight / ray_len;
	return (pixel_step * current_tile_y);
}

// void print_data(char *file, t_texture *img)
// {
// 	printf("texture-path : |%s|\n", file);
// 	printf("bits-per-pixel : |%d|\n", img->pixel_bits);
// 	printf("img hight : |%d|\n", img->hight);
// 	printf("img width : |%d|\n", img->width);
// 	printf("endian : |%d|\n", img->endianess);
// 	printf("img-address : |%p|\n", img->img);
// 	printf("byte-iterator : |%p|\n", img->iter);
// 	printf("line_lenght : |%d|\n", img->line_lenght);

// }

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
	int current_x;
	
	if (ray->side_flag == 1)
		current_x = (int)ray->horizontal_x % TILE_SIZE;
	else
		current_x = (int)ray->vertical_y % TILE_SIZE;
	ray->curr_color = get_cords_color(&data->wall_textures[ray->texture_idx],
		get_texture_x_cord(current_x, data->wall_textures[ray->texture_idx].width),
		get_texture_y_cord(current_y, data->wall_textures[ray->texture_idx].hight,
			ray->height));
}