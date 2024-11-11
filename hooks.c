/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/11 18:36:09 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_win1(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(0);
}

int  get_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return 0;
	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	return (*(unsigned int *) dst == WALL_COLOR);
}

void draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
				data->player.player_x, data->player.player_y);
}

void move_player(t_data *data, int key)
{
	mlx_put_image_to_window(data->mlx, data->win, data->player.erase_img,
				data->player.player_x, data->player.player_y);
	if (key == W || key == S)
		w_s_moves(data, key);
	if (key == D || key == A)
		d_a_moves(data, key);
}

int hooks(int key, t_data *data)
{
	// printf("key ==> %d\n", key);
	if (key == CLOSE)
		close_win1(data);
	else if (key == RIGHT || key == LEFT)
		rotate(data, key);
	else if (key == W || key == S || key == A || key == D)
		move_player(data, key);
	else
		return 0;
	draw_player(data);
	return (0);
}