/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:59:36 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/22 22:11:01 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	ini_vars(t_data *data, t_draw_line *draw, float x2, float y2)
{
	draw->dx = x2 - data->player.player_center_x;
	draw->dy = y2 - data->player.player_center_y;
	if (abs(draw->dx) > abs(draw->dy))
		draw->steps = abs(draw->dx);
	else
		draw->steps = abs(draw->dy);
	draw->x_increment = draw->dx / (float)draw->steps;
	draw->y_increment = draw->dy / (float)draw->steps;
	draw->r_s = (FOV_COLOR >> 16) & 0xFF;
	draw->g_s = (FOV_COLOR >> 8) & 0xFF;
	draw->b_s = FOV_COLOR & 0xFF;
	draw->r_e = (BLACK >> 16) & 0xFF;
	draw->g_e = (BLACK >> 8) & 0xFF;
	draw->b_e = BLACK & 0xFF;
	draw->delta_r = (float)(draw->r_e - draw->r_s) / draw->steps;
	draw->delta_g = (float)(draw->g_e - draw->g_s) / draw->steps;
	draw->delta_b = (float)(draw->b_e - draw->b_s) / draw->steps;
	draw->skip = 2;
}

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x <= 0 || x >= data->width_2d || y <= 0 || y >= data->height_2d)
		return (false);
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	return ((*(unsigned int *)dst));
}

static void	new_color(t_draw_line *draw, int i)
{
	draw->r = (draw->r_s + (i * draw->delta_r));
	draw->g = (draw->g_s + (i * draw->delta_g));
	draw->b = (draw->b_s + (i * draw->delta_b));
	draw->color = (draw->r << 16) | (draw->g << 8) | draw->b;
}

void	draw_line(t_data *data, float x2, float y2, int i)
{
	t_draw_line	draw;
	float		x;
	float		y;
	int			check_color;

	ini_vars(data, &draw, x2, y2);
	x = data->player.player_center_x;
	y = data->player.player_center_y;
	draw.color = WHITE;
	while (++i <= draw.steps)
	{
		new_color(&draw, i);
		if (draw.color == 0)
			break ;
		check_color = get_color(data, (int)x, (int)y);
		if (draw.skip < 0 && (check_color == WALL_COLOR || check_color
				== EMPTY || check_color == WHITE))
			break ;
		if (!(draw.skip >= 0 && draw.skip != 3 && draw.skip != 2
				&& check_color == WALL_COLOR))
			my_mlx_pixel_put(data, (int)x, (int)y, draw.color);
		x += draw.x_increment;
		y += draw.y_increment;
		draw.skip--;
	}
}

void	draw_fov(t_data *data, float x2, float y2)
{
	t_ray	*ray;
	int		column;
	float	delta_x;
	float	delta_y;

	ray = &(data->ray);
	ray->rayangle = data->player.angle - (data->player.fov / 2);
	if (ray->rayangle < 0)
		ray->rayangle += 360;
	column = 0;
	while (column <= WIDTH)
	{
		delta_x = cos(radian(ray->rayangle)) * FOV_LENGTH;
		delta_y = sin(radian(ray->rayangle)) * FOV_LENGTH;
		x2 = data->player.player_center_x + delta_x;
		y2 = data->player.player_center_y + delta_y;
		draw_line(data, x2, y2, -1);
		ray->rayangle += data->player.angle_step;
		column++;
	}
}
