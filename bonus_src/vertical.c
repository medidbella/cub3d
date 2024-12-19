/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:49:47 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:27:06 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double	calculate_delta_x(t_data *data, double *vertical_x
							, double *vertical_y, double rayangle)
{
	double	delta_x;

	if (rayangle > 90 && rayangle < 270)
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

void	find_vertical_point(t_data *data, double *vertical_x
							, double *vertical_y)
{
	double	delta_x;
	double	delta_y;
	double	rayangle;

	rayangle = data->ray.rayangle;
	if (rayangle == 90 || rayangle == 270)
		return ;
	if (!v_ray_to_door(data, rayangle, &delta_x))
		delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
	delta_y = tan(radian(rayangle)) * delta_x;
	*vertical_x = *vertical_x - delta_x;
	*vertical_y = *vertical_y - delta_y;
}

static bool	check_next_possition(t_data *data, t_ray *ray, int *x, int *y)
{
	double	check_x;

	if (ray->rayangle == 90 || ray->rayangle == 270
		|| ray->vertical_x < 0 || ray->vertical_x > data->width_2d
		|| ray->vertical_y < 0 || ray->vertical_y > data->height_2d)
		return (true);
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

static void	get_coords_for_direction(t_data *data, int *checks, int x, int y)
{
	(*checks)++;
	if (ft_strchr("hv", data->map[y][x]))
	{
		data->ray.hit_v_openedoor = 1;
		data->ray.openedoor_vx = data->ray.vertical_x;
		data->ray.openedoor_vy = data->ray.vertical_y;
	}
}

void	vertical_distance(t_data *data, t_ray *ray)
{
	int		x;
	int		y;
	int		checks;

	init_vars(data, ray, &checks, V_VARS);
	while (1)
	{
		find_vertical_point(data, &ray->vertical_x, &ray->vertical_y);
		if (check_next_possition(data, ray, &x, &y))
			break ;
		if (ft_strchr("1HV", data->map[y][x]))
		{
			if (ft_strchr("HV", data->map[y][x]) && ray->v_door == 0)
			{
				ray->vertical_door_flag = 1;
				ray->v_door = 1;
				continue ;
			}
			ray->vertical_distance = get_distance(data, ray->vertical_x,
					ray->vertical_y);
			break ;
		}
		if (ray->direction_flag && checks < 2 && !ray->hit_v_openedoor)
			get_coords_for_direction(data, &checks, x, y);
	}
}
