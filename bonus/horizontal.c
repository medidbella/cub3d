/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:36 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/29 17:17:49 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(t_data *data, double x, double y)
{
	return (sqrt(pow((data->player.player_x - x), 2)
			+ pow((data->player.player_y - y), 2)));
}

double	calculate_delta_y(t_data *data, double *horizontal_x
							, double *horizontal_y, double rayangle)
{
	double	delta_y;

	if (rayangle > radian(180))
	{
		if (*horizontal_x == data->player.player_x
			&& *horizontal_y == data->player.player_y)
		{
			delta_y = *horizontal_y
				- (((int)(*horizontal_y / TILE_SIZE)) * (TILE_SIZE));
			if (delta_y == 0)
				delta_y = TILE_SIZE;
		}
		else
			delta_y = TILE_SIZE;
	}
	else
	{
		if (*horizontal_x == data->player.player_x
			&& *horizontal_y == data->player.player_y)
			delta_y = (*horizontal_y)
				- (((int)((*horizontal_y) / TILE_SIZE) + 1) * TILE_SIZE);
		else
			delta_y = -TILE_SIZE;
	}
	return (delta_y);
}

void	find_horizontal_point(t_data *data, double rayangle
					, double *horizontal_x, double *horizontal_y)
{
	double	delta_x;
	double	delta_y;

	if (rayangle == 0 || rayangle == radian(180))
		return ;
	delta_y = calculate_delta_y(data, horizontal_x, horizontal_y, rayangle);
	delta_x = delta_y / tan(rayangle);
	*horizontal_x = *horizontal_x - delta_x;
	*horizontal_y = *horizontal_y - delta_y;
}

static bool	check_next_possition(t_data *data, t_ray *ray, int *x, int *y)
{
	double	check_y;

	check_y = ray->horizontal_y;
	if (ray->horizontal_y < data->player.player_y)
		check_y -= 1;
	*x = ray->horizontal_x / TILE_SIZE;
	*y = check_y / TILE_SIZE;
	if ((*y < data->height_2d && *y >= 0) && (*x >= 0
			&& *x < (int)ft_strlen(data->map[*y])))
	{
		if (data->map[*y][*x] == ' ')
			return (true);
	}
	else
		return (true);
	return (false);
}

void	horizontal_distance(t_data *data, t_ray *ray, double rayangle)
{
	int		x;
	int		y;

	ray->horizontal_y = data->player.player_y;
	ray->horizontal_x = data->player.player_x;
	ray->horizontal_distance = -1.0;
	while (1)
	{
		find_horizontal_point(data, rayangle, &ray->horizontal_x,
			&ray->horizontal_y);
		if (rayangle == 0 || rayangle == radian(180)
			|| ray->horizontal_y > data->height_2d || ray->horizontal_y < 0
			|| ray->horizontal_x > data->width_2d || ray->horizontal_x < 0
			|| check_next_possition(data, ray, &x, &y))
			break ;
		if (data->map[y][x] == '1')
		{
			ray->horizontal_distance = get_distance(data, ray->horizontal_x,
					ray->horizontal_y);
			break ;
		}
	}
}
