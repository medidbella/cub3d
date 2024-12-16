/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:47:36 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/16 15:33:35 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	find_horizontal_point(t_data *data, double *horizontal_x,
					double *horizontal_y)
{
	double	delta_x;
	double	delta_y;
	double	rayangle;

	rayangle = data->ray.rayangle;
	if (rayangle == 0 || rayangle == radian(180))
		return ;
	if (!h_ray_to_door(data, rayangle, &delta_y))
		delta_y = calculate_delta_y(data, horizontal_x, horizontal_y, rayangle);
	delta_x = delta_y / tan(rayangle);
	*horizontal_x = *horizontal_x - delta_x;
	*horizontal_y = *horizontal_y - delta_y;
}

static bool	check_next_possition(t_data *data, t_ray *ray, int *x, int *y)
{
	double	check_y;

	if (ray->rayangle == 0 || ray->rayangle == radian(180)
		|| ray->horizontal_y > data->height_2d || ray->horizontal_y < 0
		|| ray->horizontal_x > data->width_2d || ray->horizontal_x < 0)
		return (true);
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

static void	get_coords_for_direction(t_data *data, int *checks, int x, int y)
{
	(*checks)++;
	if (ft_strchr("hv", data->map[y][x]))
	{
		data->ray.hit_h_openedoor = 1;
		data->ray.openedoor_hx = data->ray.horizontal_x;
		data->ray.openedoor_hy = data->ray.horizontal_y;
	}
}

void	horizontal_distance(t_data *data, t_ray *ray)
{
	int		x;
	int		y;
	int		checks;

	init_vars(data, ray, &checks, H_VARS);
	while (1)
	{
		find_horizontal_point(data, &ray->horizontal_x, &ray->horizontal_y);
		// printf("hx: %f || hy: %f || h distance: %f\n", ray->horizontal_x, ray->horizontal_y, ray->horizontal_distance);
		// exit(0);
		if (check_next_possition(data, ray, &x, &y))
			break ;
		if (ft_strchr("1HV", data->map[y][x]))
		{
			if (ft_strchr("HV", data->map[y][x]) && ray->h_door == 0)
			{
				data->ray.horizontal_door_flag = 1;
				ray->h_door = 1;
				continue ;
			}
			ray->horizontal_distance = get_distance(data, ray->horizontal_x,
					ray->horizontal_y);
			break ;
		}
		if (ray->direction_flag && checks < 2 && !ray->hit_h_openedoor)
			get_coords_for_direction(data, &checks, x, y);
	}
}
