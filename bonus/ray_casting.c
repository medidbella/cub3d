/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:10:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 13:07:45 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	height_and_texture(t_data *data, t_ray *ray)
{
	if (ray->side_flag == 1)
	{
		if (ray->rayangle >= 180)
			ray->texture_idx = S_INDEX;
		else
			ray->texture_idx = N_INDEX;
	}
	else
	{
		if ((ray->rayangle >= 0 && ray->rayangle <= 90)
			|| ray->rayangle >= 270)
			ray->texture_idx = W_INDEX;
		else
			ray->texture_idx = E_INDEX;
	}
	ray->height = ((double)TILE_SIZE / ray->distance)
		* data->player.distance_to_project_plan;
}

void	draw_column(t_data *data, t_ray *ray, int column)
{
	int	start;
	int	end;
	int	i;

	height_and_texture(data, ray);
	start = (HEIGHT - ray->height) / 2;
	end = start + ray->height;
	if (end > HEIGHT)
		end = HEIGHT;
	i = -1;
	while (++i < start)
		my_mlx_pixel_put(data, column, i, data->ceiling_color);
	i = -1;
	if (start > 0)
		i = start - 1;
	while (++i < end)
	{
		get_texture_color(data, ray, i - start);
		my_mlx_pixel_put(data, column, i, ray->curr_color);
	}
	while (i < HEIGHT)
		my_mlx_pixel_put(data, column, i++, data->floor_color);
}

void	real_distance(t_ray *ray, t_data *data)
{
	float	distance;

	if (ray->direction_flag)
	{
		if (ray->vertical_distance == -1)
			ray->direction_ray_distance = ray->horizontal_distance;
		else if (ray->horizontal_distance == -1)
			ray->direction_ray_distance = ray->vertical_distance;
		else
		{
			ray->direction_ray_distance = ray->horizontal_distance;
			distance = ray->vertical_distance;
			if (ray->direction_ray_distance > distance)
				ray->direction_ray_distance = distance;
		}
	}
	if (ray->horizontal_distance != -1)
		ray->horizontal_distance = cos(radian(ray->rayangle
					- data->player.angle)) * ray->horizontal_distance;
	if (ray->vertical_distance != -1)
		ray->vertical_distance = cos(radian(ray->rayangle
					- data->player.angle)) * ray->vertical_distance;
}

int	small_distance(t_ray *ray)
{
	if (ray->horizontal_distance == -1)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
		return (ray->v_door);
	}
	else if (ray->vertical_distance == -1)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
		return (ray->h_door);
	}
	else if (ray->vertical_distance <= ray->horizontal_distance)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
		return (ray->v_door);
	}
	else if (ray->horizontal_distance < ray->vertical_distance)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
		return (ray->h_door);
	}
	return (0);
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	int		column;

	ray = &(data->ray);
	initialize_vars(data, ray, &column);
	while (column <= WIDTH)
	{
		if (column == ((WIDTH / 2) - 1))
			ray->direction_flag = 1;
		if (column == (WIDTH / 2))
			direction_of_player(data);
		ray->h_door = 0;
		ray->v_door = 0;
		horizontal_distance(data, ray);
		vertical_distance(data, ray);
		// if (data->debug == 9 && ray->direction_flag == 1)
		// {
		// 	printf("Hx: %f || Hy: %f\n", ray->horizontal_x, ray->horizontal_y);
		// 	// printf("Vx: %f || Vy: %f\n", ray->vertical_x, ray->vertical_y);
		// 	printf("hit H: %d || hit V: %d\n", ray->hit_h_openedoor, ray->hit_v_openedoor);
		// 	exit(0);
		// }
		real_distance(ray, data);
		ray->door = small_distance(ray);
		draw_column(data, ray, column);
		column++;
		ray->rayangle += data->player.angle_step;
		if (ray->rayangle >= 360)
			ray->rayangle -= 360;
		ray->direction_flag = 0;
	}
}
