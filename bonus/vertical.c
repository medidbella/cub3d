/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:49:47 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/06 16:21:45 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_delta_x(t_data *data, double *vertical_x
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

void	find_vertical_point(t_data *data, double rayangle, double *vertical_x
							, double *vertical_y)
{
	double	delta_x;
	double	delta_y;

	if (rayangle == radian(90) || rayangle == radian(270))
		return ;
	if (!v_ray_to_door(data, rayangle, &delta_x))
		delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
	delta_y = tan(rayangle) * delta_x;
	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y - delta_y;
}

static bool	check_next_possition(t_data *data, t_ray *ray, int *x, int *y)
{
	double	check_x;

	check_x = ray->vertical_x;
	if (ray->vertical_x < data->player.player_x)
		check_x -= 1;
	*x = check_x / TILE_SIZE;
	*y = ray->vertical_y / TILE_SIZE;
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

void	vertical_distance(t_data *data, t_ray *ray, double rayangle)
{
	int		x;
	int		y;

	ray->vertical_y = data->player.player_y;
	ray->vertical_x = data->player.player_x;
	ray->vertical_distance = -1.0;
	while (1)
	{
		find_vertical_point(data, rayangle, &ray->vertical_x, &ray->vertical_y);
		if (rayangle == radian(90) || rayangle == radian(270)
			|| ray->vertical_x < 0 || ray->vertical_x > data->width_2d
			|| ray->vertical_y < 0 || ray->vertical_y > data->height_2d
			|| check_next_possition(data, ray, &x, &y))
			break ;
		if (ft_strchr("1HV", data->map[y][x]))
		{
			if (ft_strchr("HV", data->map[y][x]))
				ray->v_door = 1;
			ray->vertical_distance = get_distance(data, ray->vertical_x,
					ray->vertical_y);
			break ;
		}
	}
}
