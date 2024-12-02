/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:49:47 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/02 23:11:30 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_delta_x(t_data *data, double *vertical_x
							, double *vertical_y, double rayangle)
{
	double	delta_x;

	if (rayangle > radian(90) && rayangle < radian(270))
	{
		if (*vertical_x == data->player.player_x
			&& *vertical_y == data->player.player_y)
		{
			delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE))
					* TILE_SIZE);
			if (delta_x == 0)
				delta_x = TILE_SIZE;
		}
		else
			delta_x = TILE_SIZE;
	}
	else
	{
		if (*vertical_x == data->player.player_x
			&& *vertical_y == data->player.player_y)
			delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE) + 1)
					* TILE_SIZE);
		else
			delta_x = -TILE_SIZE;
	}
	return (delta_x);
}

static void	find_vertical_point(t_data *data, double rayangle
				, double *vertical_x, double *vertical_y)
{
	double	delta_x;
	double	delta_y;

	if (rayangle == radian(90) || rayangle == radian(270))
		return ;
	delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
	delta_y = tan(rayangle) * delta_x;
	// printf("ray angle ==> %f || tan ==> %f\n", rayangle, tan(rayangle));
	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y - delta_y;
	
	// printf("delta x: %f || delta y: %f\n", delta_x, delta_y);
	// printf("V_x: %f || V_y: %f\n", *vertical_x, *vertical_y);
}

static bool	check_next_possition(t_data *data, t_ray *ray, int *x, int *y)
{
	double	check_x;

	check_x = ray->vertical_x;
	if (ray->vertical_x < data->player.player_x)
		check_x -= 1;
	*x = check_x / TILE_SIZE;
	*y = ray->vertical_y / TILE_SIZE;
	// printf("index x: %d || index y: %d\n", *x, *y);
	if ((*y < data->height_2d && *y >= 0)
		&& (*x >= 0 && *x < (int)ft_strlen(data->map[*y])))
	{
		if (data->map[*y][*x] == ' ')
			return (true);
	}
	else
		return (true);
	return (false);
}

static void	get_door_distance(t_data *data, t_ray *ray, double rayangle)
{
	double	x_door;
	double	y_door;
	double	delta_x;
	double	delta_y;

	delta_x = (double)TILE_SIZE / 2;
	delta_y = tan(rayangle) * delta_x;
	x_door = ray->vertical_x - delta_x;
	y_door = ray->vertical_y - delta_y;

	ray->vertical_distance = get_distance(data, x_door, y_door);
		ray->v_door = 1;
}

void	vertical_distance(t_data *data, t_ray *ray, double rayangle)
{
	int		x;
	int		y;

	ray->vertical_y = data->player.player_y;
	ray->vertical_x = data->player.player_x;
	ray->vertical_distance = -1.0;
	// printf("Px: %f || Py: %f\n", data->player.player_x, data->player.player_y);
	while (1)
	{
		find_vertical_point(data, rayangle, &ray->vertical_x, &ray->vertical_y);
		// printf("=======================\n");
		printf("V_x: %f || V_y: %f\n", ray->vertical_x, ray->vertical_y);
		if (rayangle == radian(90) || rayangle == radian(270)
			|| ray->vertical_x < 0 || ray->vertical_x > data->width_2d
			|| ray->vertical_y < 0 || ray->vertical_y > data->height_2d
			|| check_next_possition(data, ray, &x, &y))
			break ;
		if (data->map[y][x] == '1')
		{
			printf("Hitting wall\n");
			ray->vertical_distance = get_distance(data, ray->vertical_x,
				ray->vertical_y);
		}
		else if (data->map[y][x] == 'D')
		{
			printf("hitting door\n");
			get_door_distance(data, ray, rayangle);
		}
		else
			continue ;
		break ;
	}
}
