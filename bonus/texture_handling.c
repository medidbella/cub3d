/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:01:07 by midbella          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:29 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_cords_color(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->iter + (y * img->line_length + x * (img->pixel_bits / 8));
	return (*(int *)dst);
}

void	texture_init(void *mlx, t_texture *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(mlx, file_path, &texture->width,
			&texture->hight);
	texture->iter = mlx_get_data_addr(texture->img, &texture->pixel_bits,
			&texture->line_length, &texture->endianess);
}

void	initialize_wall_textures(t_data *data, t_config *parsed_data)
{
	int		i;

	i = 0;
	while (i <= 3)
	{
		texture_init(data->mlx, &data->wall_textures[i],
			parsed_data->textures_paths[i]);
		i++;
	}
	if (parsed_data->door_flag == 1)
		texture_init(data->mlx, &data->wall_textures[i],
			parsed_data->textures_paths[i]);
}

void	set_scale(t_data *data, t_ray *ray, float *scale1, float *scale2)
{
	*scale1 = (float)data->wall_textures[ray->texture_idx].width / TILE_SIZE;
	*scale2 = (float)data->wall_textures[ray->texture_idx].hight / ray->height;
	if (ray->door)
	{
		*scale1 = (float)data->wall_textures[DOOR_IDX].width / TILE_SIZE;
		*scale2 = (float)data->wall_textures[DOOR_IDX].hight / ray->height;
	}
}

void	get_texture_color(t_data *data, t_ray *ray, int current_y)
{
	float	x_scale;
	float	y_scale;
	int		current_x;

	current_x = 0;
	set_scale(data, ray, &x_scale, &y_scale);
	if (ray->texture_idx == N_INDEX)
		current_x = (int)ray->horizontal_x % TILE_SIZE;
	else if (ray->texture_idx == S_INDEX)
		current_x = TILE_SIZE - ((int)ray->horizontal_x % TILE_SIZE);
	else if (ray->texture_idx == E_INDEX)
		current_x = (int)ray->vertical_y % TILE_SIZE;
	else if (ray->texture_idx == W_INDEX)
		current_x = TILE_SIZE - ((int)ray->vertical_y % TILE_SIZE);
	if (ray->door)
		ray->curr_color = get_cords_color(&data->wall_textures[WALL_INDEX],
				current_x * x_scale, current_y * y_scale);
	else
		ray->curr_color = get_cords_color(&data->wall_textures
			[ray->texture_idx], current_x * x_scale, current_y * y_scale);
}
