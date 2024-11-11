/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:10:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/11 18:31:59 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void find_wall(t_data *data, t_ray *ray)
{

	int x1 = data->player.x_c;
	int y1 = data->player.y_c;
	int x2 = ray->x;
	int y2 = ray->y;
	
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1; // step in x
	int sy = (y1 < y2) ? 1 : -1; // step in y
	int err = dx - dy; // error value

	while (1)
	{
		// if (!get_color(data, x1, y1))
		// 	my_mlx_pixel_put(data, x1, y1, color);
		if (get_color(data, x1, y1))
		{
			ray->wall_x = x1;
			ray->wall_y = y1;
			break ;
		}
		if (x1 == x2 && y1 == y2) break; // end point reached
		int err2 = err * 2;
		if (err2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

double get_distance(t_data *data, double x, double y)
{
	return (sqrt(pow((data->player.x_c - x), 2) + pow((data->player.y_c - y), 2)));
}


void find_horizontal(double rayangle, double *horizontal_x, double *horizontal_y)
{
	double delta_x;
	double delta_y;
	// printf ("horizontah Y ###==> %f\n", *horizontal_y);

	if ((rayangle >= 0 && rayangle <= 90) || (rayangle >= 270))
	{
		// printf ("==> A\n");
		if ((int)*horizontal_y % TILE_SIZE != 0)
			delta_y = *horizontal_y - ((int)(*horizontal_y / TILE_SIZE) * TILE_SIZE);
		else
			delta_y = TILE_SIZE;
	}
	else
	{
		// printf ("==> B\n");
		if ((int)*horizontal_y % TILE_SIZE != 0)
		{
			// printf("==> 1\n");
			delta_y = (*horizontal_y) - (((int)((*horizontal_y) / (double)TILE_SIZE) + 1) * (double)TILE_SIZE);
			// printf ("delta Y ###==> %f\n", delta_y);
			// exit(0);

		}
		else
		{
			// printf("==> 2\n");
			delta_y = -TILE_SIZE;
		}
	}
	delta_x = tan(radian(rayangle)) * delta_y;
	
	// printf("delta x : %f || delta y : %f\n", delta_x, delta_y);
	

	*horizontal_x = *horizontal_x + delta_x;
	*horizontal_y = *horizontal_y - delta_y;

}

double distance_h(t_data *data, double rayangle)
{
	double distance;
	double horizontal_y, horizontal_x;

	horizontal_y = data->player.y_c;
	horizontal_x = data->player.x_c;
	
	while (1)
	{
		find_horizontal(rayangle, &horizontal_x, &horizontal_y);
		// printf("first hor x: %f || first hor y: %f\n", horizontal_x, horizontal_y);
		
		// printf ("checking... \n");
		
		if (horizontal_y > HEIGHT_2D || horizontal_x > WIDTH_2D || horizontal_y < 0 || horizontal_x < 0)
		{
			// printf("outside the map 2D\n");
			distance = -1.0;
			// printf("distance : %f\n", distance);
			break ;
		}
			double check_y = horizontal_y;
		if ((rayangle >= 0 && rayangle <= 90) || (rayangle >= 270))
			check_y -= 1;
		if (get_color(data, horizontal_x, check_y))
		{
			distance = get_distance(data, horizontal_x, check_y);
			// printf("point(%f, %f)\n", horizontal_x, horizontal_y);
			// printf("distance : %f\n", distance);
			break ;
		}
	}
	return (distance);
}

void find_vertical(double rayangle, double *vertical_x, double *vertical_y)
{
	double delta_x;
	double delta_y;

	if (rayangle >= 180)
	{
		// printf ("==> A\n");
		if ((int)*vertical_x % TILE_SIZE != 0)
			delta_x = *vertical_x - ((int)(*vertical_x / TILE_SIZE) * TILE_SIZE);
		else
			delta_x = TILE_SIZE;
	}
	else
	{
		// printf ("==> B\n");
		if ((int)*vertical_x % TILE_SIZE != 0)
		{
			// printf("==> 1\n");
			delta_x = *vertical_x - (((int)(*vertical_x / (double)TILE_SIZE) + 1) * (double)TILE_SIZE);
		}
		else
			delta_x = -TILE_SIZE;
	}
	delta_y = delta_x / tan(radian(rayangle));
	
	// printf("delta x : %f || delta y : %f\n", delta_x, delta_y);
	

	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y + delta_y;

}

double	distance_v(t_data *data, double rayangle)
{
	double distance;
	double vertical_y, vertical_x;

	vertical_y = data->player.y_c;
	vertical_x = data->player.x_c;

	while (1)
	{
		// printf ("cheking ...\n");
		find_vertical(rayangle, &vertical_x, &vertical_y);
		// printf("vert x: %f || vert y: %f\n", vertical_x, vertical_y);
		
		if (vertical_y > HEIGHT_2D || vertical_x > WIDTH_2D || vertical_x < 0 ||  vertical_y < 0)
		{
			// printf("outside the map 2D\n");
			distance = -1.0;
			// printf("distance : %f\n", distance);
			break ;
		}
		
		double check_x = vertical_x;
		if (rayangle >= 180)
			check_x -= 1;
		if (get_color(data, check_x, vertical_y))
		{
			distance = get_distance(data, check_x, vertical_y);
			// printf("point(%f, %f)\n", vertical_x, vertical_y);
			// printf("distance : %f\n", distance);
			break ;
		}
	}
	return (distance);
}

void ray_casting(t_data *data)
{
	int		colums;
	// double	distance;
	double	rayangle;
	double	raystep;
	double horizontal_distance;
	double vertical_distance;

	colums = 0;
	rayangle = data->player.angle - (FOV / 2);
	if (rayangle < 0)
		rayangle += 360;
	printf("ray angle %f\n\n", rayangle);
	raystep = ((double)FOV / WIDTH);
	
	
	while (colums < WIDTH)
	{


		horizontal_distance = distance_h(data, rayangle);
		printf("horizontal distance : %f\n", horizontal_distance);
		printf ("\n========================\n");
		// exit(0);

		vertical_distance = distance_v(data, rayangle);
		printf("vertical distance : %f\n", vertical_distance);
		
		
		colums++;
		rayangle += raystep;
	}
}
