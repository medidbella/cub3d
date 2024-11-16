/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:10:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/16 09:41:04 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double get_distance(t_data *data, double x, double y)
{
	return (sqrt(pow((data->player.x_c - x), 2) + pow((data->player.y_c - y), 2)));
}

int find_horizontal(t_data *data, double rayangle, double *horizontal_x, double *horizontal_y)
{
	double delta_x;
	double delta_y;

	if (rayangle == 0 || rayangle == 180)
		return (1);
	if (rayangle > 180)
	{
		if (*horizontal_x == data->player.x_c && *horizontal_y == data->player.y_c)
		{
			delta_y = *horizontal_y - ((int)(*horizontal_y / TILE_SIZE) * TILE_SIZE);
			if (delta_y == 0)
				delta_y = TILE_SIZE;
		}
		else
			delta_y = TILE_SIZE;
	}
	else
	{
		if (*horizontal_x == data->player.x_c && *horizontal_y == data->player.y_c)
			delta_y = (*horizontal_y) - (((int)((*horizontal_y) / (double)TILE_SIZE) + 1) * (double)TILE_SIZE);
		else
			delta_y = -TILE_SIZE;
	}
	delta_x = delta_y / tan(radian(rayangle));
	*horizontal_x = *horizontal_x - delta_x;
	*horizontal_y = *horizontal_y - delta_y;
	return (0);
}

void distance_h(t_data *data, t_ray *ray, double rayangle)
{
	double distance;

	ray->horizontal_y = data->player.y_c;
	ray->horizontal_x = data->player.x_c;

	int i = 0;
	while (1)
	{
		if (find_horizontal(data, rayangle, &ray->horizontal_x, &ray->horizontal_y))
		{
			distance = -1.0;
			break ;
		}
		if (ray->horizontal_y > HEIGHT_2D || ray->horizontal_x > WIDTH_2D || ray->horizontal_y < 0 || ray->horizontal_x < 0)
		{
			distance = -1.0;
			break ;
		}
		double check_y = ray->horizontal_y;
		if (rayangle >= 180)
			check_y -= 1;
		if (get_color(data, ray->horizontal_x, check_y))
		{
			distance = get_distance(data, ray->horizontal_x, ray->horizontal_y);
			break ;
		}
	}
	ray->horizontal_distance = distance;
}

int find_vertical(t_data *data, double rayangle, double *vertical_x, double *vertical_y, int column)
{
	double delta_x;
	double delta_y;

	if (rayangle == 90 || rayangle == 270)
		return (1);
	if (rayangle > 90 && rayangle < 270)
	{
		if (*vertical_x == data->player.x_c && *vertical_y == data->player.y_c)
		{	
			delta_x = *vertical_x - ((int)(*vertical_x / TILE_SIZE) * TILE_SIZE);
			if (delta_x == 0)
				delta_x = TILE_SIZE;
		}
		else
			delta_x = TILE_SIZE;
	}
	else
	{
		if (*vertical_x == data->player.x_c && *vertical_y == data->player.y_c)
			delta_x = *vertical_x - (((int)(*vertical_x / (double)TILE_SIZE) + 1) * (double)TILE_SIZE);
		else
			delta_x = -TILE_SIZE;
	}
	delta_y = tan(radian(rayangle)) * delta_x;

	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y - delta_y;
	return (0);
}

void	distance_v(t_data *data, t_ray *ray, double rayangle, int column)
{
	double distance;

	ray->vertical_y = data->player.y_c;
	ray->vertical_x = data->player.x_c;

	while (1)
	{
		if (find_vertical(data, rayangle, &ray->vertical_x, &ray->vertical_y, column))
		{
			distance = -1.0;
			break ;
		}
		if (ray->vertical_y > HEIGHT_2D || ray->vertical_x > WIDTH_2D || ray->vertical_x < 0 ||  ray->vertical_y < 0)
		{
			distance = -1.0;
			break ;
		}
		
		double check_x = ray->vertical_x;
		if (rayangle >= 90 && rayangle <= 270)
			check_x -= 1;
		if (get_color(data, check_x, ray->vertical_y))
		{
			distance = get_distance(data, ray->vertical_x, ray->vertical_y);
			break ;
		}
	}
	ray->vertical_distance = distance;
}

void	tall_and_color(t_data *data, t_ray *ray)
{
	if (ray->side_flag == 1)
	{
		if (ray->rayangle >= 180)
			ray->curr_color = NORTH_CLR;
		else
			ray->curr_color = SOUTH_CLR;
	}
	else
	{
		if ((ray->rayangle >= 0 && ray->rayangle <= 90) || ray->rayangle >= 270)
			ray->curr_color = EAST_CLR;
		else
			ray->curr_color = WEST_CLR;
	}
	ray->tall = ((double)TILE_SIZE / ray->distance) * data->player.distance_to_project_plan;
}

void draw_column(t_data *data, t_ray *ray, int column)
{
	tall_and_color(data, ray);

	int start = (HEIGHT - ray->tall) / 2;
	if (start < 0)
		start -= start;
	int end = start + ray->tall;
	if (end > HEIGHT)
		end = HEIGHT;
	int i = 0;

	while (i < start)
	{
		my_mlx_pixel_put(data, column, i, 0x0000ff);
		i++;
	}
	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(data, column, i, ray->curr_color);
		i++;
	}
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(data, column, i, BLACK);
		i++;
	}
}

void real_distance(t_ray *ray, t_data *data)
{
	if (ray-> horizontal_distance != -1)
		ray->horizontal_distance = cos(radian(ray->rayangle)) * ray->horizontal_distance;
	if (ray->vertical_distance != -1)
		ray->vertical_distance = cos(radian(ray->rayangle)) * ray->vertical_distance;
}

void draw_fov(t_data *data, t_ray *ray)
{
	if (ray->side_flag == 1)
		bresenham(data->player.x_c, data->player.y_c, ray->horizontal_x, ray->horizontal_y, DIR_COLOR, data);
	else
		bresenham(data->player.x_c, data->player.y_c, ray->vertical_x, ray->vertical_y, DIR_COLOR, data);

}

void	fov_coordinates(t_data *data, t_ray *ray, int *first_fov, int which)
{
	if (ray->side_flag == 1)
	{
		if (which == 1)
		{
			data->player.first_x_fov = ray->horizontal_x;
			data->player.first_y_fov = ray->horizontal_y;
		}
		else
		{
			data->player.last_x_fov = ray->horizontal_x;
			data->player.last_y_fov = ray->horizontal_y;	
		}
	}
	else
	{
		if (which == 1)
		{
			data->player.first_x_fov = ray->vertical_x;
			data->player.first_x_fov = ray->vertical_y;
		}
		else
		{
			data->player.last_x_fov = ray->vertical_x;
			data->player.last_y_fov = ray->vertical_y;
		}
	}
	*first_fov = 1;
}

void small_distance(t_data *data, t_ray *ray, int *first_fov)
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

void ray_casting(t_data *data)
{
	t_ray	ray;
	int		column;
	int		first_fov;

	first_fov = 0;
	column = 0;
	ray.rayangle = data->player.angle - (FOV / 2);
	if (ray.rayangle < 0)
		ray.rayangle += 360;
	ray.raystep = ((double)FOV / WIDTH);
	
	printf("XP : %f || YP : %f\n", data->player.x_c, data->player.y_c);
	while (column <= WIDTH)
	{
		distance_h(data, &ray, ray.rayangle);
		distance_v(data, &ray, ray.rayangle, column);
		// real_distance(&ray, data);
		small_distance(data, &ray, &first_fov);


		draw_fov(data, &ray);
		draw_column(data, &ray, column);
		
		column++;
		ray.rayangle += ray.raystep;
		if (ray.rayangle > 360)
			ray.rayangle -= 360;
	}
	fov_coordinates(data, &ray, &first_fov, 2);
}
