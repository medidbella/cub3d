/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:01:07 by midbella          #+#    #+#             */
/*   Updated: 2024/11/28 17:55:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_wall_textures_memory(t_data *data, t_texture *my_textures)
{
	int	i;

	i = 0;
	while (i <= 3 + (data->door_flag == 1))
	{
		mlx_destroy_image(data->mlx, my_textures[i].img);
		i++;
	}
}

int	get_cords_color(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
	return (*(int *)dst);
}

void	texture_init(void *mlx, t_texture *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(mlx, file_path, &texture->width,
		&texture->hight);
	if (!texture->img)
		printf("%s\n", file_path);
	texture->iter = mlx_get_data_addr(texture->img, &texture->pixel_bits,
		&texture->line_lenght, &texture->endianess);
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

void	get_texture_color(t_data *data, t_ray *ray, int current_y)
{
	float	x_scale;
	float	y_scale;
	int		current_x;

	current_x = 0;
	x_scale = (float)data->wall_textures[ray->texture_idx].hight / TILE_SIZE;
	y_scale = (float)data->wall_textures[ray->texture_idx].width / ray->height;
	if (ray->texture_idx == N_INDEX)
		current_x = (int)ray->horizontal_x % TILE_SIZE;
	else if (ray->texture_idx == S_INDEX)
		current_x = TILE_SIZE - ((int)ray->horizontal_x % TILE_SIZE);
	else if (ray->texture_idx == E_INDEX)
		current_x = (int)ray->vertical_y % TILE_SIZE;
	else if (ray->texture_idx == W_INDEX)
		current_x = TILE_SIZE - ((int)ray->vertical_y % TILE_SIZE);
	ray->curr_color = get_cords_color(&data->wall_textures[ray->texture_idx],
			current_x * x_scale, current_y * y_scale);
}
