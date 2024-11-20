/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/20 17:24:39 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_win1(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(0);
}

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= data->width_2d || y >= data->height_2d || x <= 0 || y <= 0)
		return (0);
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x
			* (data->img_2d.bits_per_pixel / 8));
	return (*(unsigned int *) dst == WALL_COLOR);
}

void	draw_map2d(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
		data->player.player_x, data->player.player_y);
}

int	check_keys(t_data *data)
{
	if (!data->keys[0] && !data->keys[1] && !data->keys[2]
		&& !data->keys[3] && !data->keys[4] && !data->keys[5]
		&& !data->keys[6])
		return 0;
	return 1;
}

int	loop_rendering(t_data *data)
{
	if (!check_keys(data))
		return 0;
	if (data->keys[6])
		close_win1(data);
	rotate(data);
	move_player(data);
	draw(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_map2d(data);
	return (0);
}
