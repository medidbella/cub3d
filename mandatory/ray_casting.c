/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:33:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/02 23:14:31 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_data *data, t_ray *ray, t_draw_line *line)
{
	line->x1 = data->player.player_x
		+ (data->player.size_x / 2);
	line->y1 = data->player.player_y
		+ (data->player.size_y / 2);
	if (ray->side_flag == 1)
	{
		line->x2 = ray->horizontal_x;
		line->y2 = ray->horizontal_y;
	}
	else
	{
		line->x2 = ray->vertical_x;
		line->y2 = ray->vertical_y;
	}
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y1 < line->y2)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	bresenham(t_data *data, t_ray *ray)
{
	t_draw_line	line;
	int			index_x;
	int			index_y;

	init_values(data, ray, &line);
	while (1)
	{
		index_x = (line.x1 / TILE_SIZE) - ((int)line.x1 % TILE_SIZE == 0
				&& data->player.player_x > line.x1);
		index_y = (line.y1 / TILE_SIZE) - ((int)line.y1 % TILE_SIZE == 0
				&& data->player.player_y > line.y1);
		if (!((int)index_y < data->height_2d
				&& (int)index_y >= 0 && (int)index_x >= 0
				&& (int)index_x < (int)ft_strlen(data->map[(int)index_y])))
			break ;
		if (!ft_strchr("NSEW0", data->map[(int)index_y][(int)index_x]))
			break ;
		my_mlx_pixel_put(data, line.x1, line.y1, 0xFF0000);
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line.err2 = line.err * 2;
		if (line.err2 > -(line.dy))
		{
			line.err -= line.dy;
			line.x1 += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			line.y1 += line.sy;
		}
	}
}

// static void	draw_fov(t_data *data, t_ray *ray)
// {
// 	bresenham(data, ray);
// }

//// the top lines are temp, only for debuging //////

static void	height_and_texture(t_data *data, t_ray *ray)
{
	if (ray->side_flag == 1)
	{
		if (ray->rayangle >= radian(180))
			ray->texture_idx = S_INDEX;
		else
			ray->texture_idx = N_INDEX;
	}
	else
	{
		if ((ray->rayangle >= 0 && ray->rayangle <= radian(90))
			|| ray->rayangle >= radian(270))
			ray->texture_idx = W_INDEX;
		else
			ray->texture_idx = E_INDEX;
	}
	ray->height = ((double)TILE_SIZE / ray->distance)
		* data->player.distance_to_project_plan;
}

static void	draw_column(t_data *data, t_ray *ray, int column)
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
		if (data->door)
			ray->curr_color = 0xFFFFFF;
		else
			get_texture_color(data, ray, i - start);
		my_mlx_pixel_put(data, column, i, ray->curr_color);
	}
	while (i < HEIGHT)
		my_mlx_pixel_put(data, column, i++, data->floor_color);
}

static void	real_distance(t_ray *ray, t_data *data)
{
	if (ray->horizontal_distance != -1)
		ray->horizontal_distance = cos(ray->rayangle - data->player.angle)
			* ray->horizontal_distance;
	if (ray->vertical_distance != -1)
		ray->vertical_distance = cos(ray->rayangle - data->player.angle)
			* ray->vertical_distance;
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
	t_ray	ray;
	int		column;

	column = 0;
	ray.rayangle = data->player.angle - (data->player.fov / 2);
	if (ray.rayangle < 0)
		ray.rayangle += radian(360);
	printf("first ray angle: %f\n\n", ray.rayangle * 180 / M_PI);
	data->debug = 0;
	while (column <= WIDTH)
	{
		ray.h_door = 0;
		ray.v_door = 0;
		printf("------------- horizontal -----------------\n");
		horizontal_distance(data, &ray, ray.rayangle);
		printf("-------------------------------------------\n\n");
		printf("--------------- vertical -----------------\n");
		vertical_distance(data, &ray, ray.rayangle);
		printf("-------------------------------------------\n\n");


		printf("H distance: %f\n", ray.horizontal_distance);
		printf("V distance: %f\n", ray.vertical_distance);

		real_distance(&ray, data);
		data->door = small_distance(&ray);

		if (data->debug == 0)
		{
			printf("door ==> %d\n", data->door);
			printf("ray angle: %f\n", ray.rayangle);
			exit(0);
		}

		// draw_fov(data, &ray);
		draw_column(data, &ray, column);
		column++;
		ray.rayangle += data->player.angle_step;
		if (ray.rayangle > radian(360))
			ray.rayangle -= radian(360);
		data->debug++;
	}
}
