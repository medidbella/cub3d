/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/15 18:49:13 by alaktari         ###   ########.fr       */
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

	if (x >= WIDTH_2D || y >= HEIGHT_2D || x <= 0 || y <= 0)
		return 0;
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x * (data->img_2d.bits_per_pixel / 8));
	return (*(unsigned int *) dst == WALL_COLOR);
}

void draw_player(t_data *data)
{
	draw_direction(data, DIR_COLOR);
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
				data->player.player_x, data->player.player_y);
}

void move_player(t_data *data, int key)
{
	mlx_put_image_to_window(data->mlx, data->win, data->player.erase_img,
				data->player.player_x, data->player.player_y);
	// printf("key ==> %d\n", key);
	if (key == W || key == S)
		w_s_moves(data, key);
	if (key == D || key == A)
		d_a_moves(data, key);
	printf("x_p: %f || y_p: %f\n", data->player.x_c, data->player.y_c);
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

	// if (data->player.x_c == 32.000000 && data->player.y_c == 100.000000)
	// {
	// 	printf("hiiiihooo\n");
	// 	exit(0);
	// }

	printf("angle : %f\n", data->player.angle);
	printf("x_p: %f || y_p: %f || angle_p: %f\n", data->player.x_c, data->player.y_c, data->player.angle);
	draw(data);
		ray_casting(data);
	// if (data->player.x_c == 32.000000 && data->player.y_c == 100.000000)
	// {
	// 	printf("hiiiihooo\n");
	// 	// exit(0);
	// }
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_player(data);

	return (0);
}