/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:10:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/21 09:54:08 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	height_and_color(t_data *data, t_ray *ray)
{
	if (ray->side_flag == 1)
	{
		if (ray->rayangle >= radian(180))
			ray->curr_color = NORTH_CLR;
		else
			ray->curr_color = SOUTH_CLR;
	}
	else
	{
		if ((ray->rayangle >= 0 && ray->rayangle <= radian(90))
			|| ray->rayangle >= radian(270))
			ray->curr_color = EAST_CLR;
		else
			ray->curr_color = WEST_CLR;
	}
	ray->height = ((double)TILE_SIZE / ray->distance)
		* data->player.distance_to_project_plan;
}

void	draw_column(t_data *data, t_ray *ray, int column)
{
	int	start;
	int	end;
	int	i;

	height_and_color(data, ray);
	start = (HEIGHT - ray->height) / 2;
	if (start < 0)
		start = 0;
	end = start + ray->height;
	if (end > HEIGHT)
		end = HEIGHT;
	i = -1;
	while (++i < start)
		my_mlx_pixel_put(data, column, i, data->ceiling_color);
	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(data, column, i, ray->curr_color);
		i++;
	}
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(data, column, i, data->floor_color);
		i++;
	}
}

void	real_distance(t_ray *ray, t_data *data)
{
	if (ray->horizontal_distance != -1)
		ray->horizontal_distance = cos(ray->rayangle - data->player.angle)
			* ray->horizontal_distance;
	if (ray->vertical_distance != -1)
		ray->vertical_distance = cos(ray->rayangle - data->player.angle)
			* ray->vertical_distance;
}

void	small_distance(t_data *data, t_ray *ray, int *first_fov)
{
	if (ray->horizontal_distance == -1)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
	}
	else if (ray->vertical_distance == -1)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
	}
	else if (ray->vertical_distance <= ray->horizontal_distance)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
	}
	else if (ray->horizontal_distance < ray->vertical_distance)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
	}
	if (*first_fov == 0)
		fov_coordinates(data, ray, first_fov, 1);
}

void	ray_casting(t_data *data)
{
	t_ray	ray;
	int		column;
	int		first_fov;

	first_fov = 0;
	column = 0;
	ray.rayangle = data->player.angle - (data->player.fov / 2);
	if (ray.rayangle < 0)
		ray.rayangle += radian(360);
	while (column <= WIDTH)
	{
		horizontal_distance(data, &ray, ray.rayangle);
		vertical_distance(data, &ray, ray.rayangle, column);
		real_distance(&ray, data);
		small_distance(data, &ray, &first_fov);
		draw_fov(data, &ray);
		draw_column(data, &ray, column);
		column++;
		ray.rayangle += data->player.angle_step;
		if (ray.rayangle > radian(360))
			ray.rayangle -= radian(360);
	}
}
