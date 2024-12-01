/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/01 12:03:04 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_textures_memory(data->mlx, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_image(data->mlx, data->player.erase_img);
	mlx_destroy_image(data->mlx, data->player.player_img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	move_player(t_data *data)
{
	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
	data->player.mini_x = data->player.player_x
		* data->scale - (data->mini_width / 2);
	data->player.mini_y = data->player.player_y
		* data->scale - (data->mini_height / 2);
}

int	check_keys(t_data *data)
{
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG] && !data->keys[W_FLAG]
		&& !data->keys[S_FLAG] && !data->keys[D_FLAG] && !data->keys[A_FLAG]
		&& !data->keys[CLOSE_FLAG] && !data->keys[MOUSE_FLAG])
		return (0);
	return (1);
}

void	mouse_events(t_data *data)
{
	int	x;
	int y;
	int	delta_x;

	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (data->mouse_x == x)
		return ;
	data->keys[MOUSE_FLAG] = 1;
	delta_x = x - (WIDTH / 2);
	data->player.angle += delta_x * SENSITIVITY;
	if (data->player.angle > radian(360))
		data->player.angle -= radian(360);
	else if (data->player.angle < 0)
		data->player.angle += radian(360);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
}

int	loop_rendering(t_data *data)
{
	mouse_events(data);
	if (!check_keys(data))
		return (0);
	if (data->keys[6])
		close_win(data);
	rotate(data);
	move_player(data);
	raplayer_yasting(data);
	draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	// draw_fov(data);
	draw_player(data);
	data->keys[MOUSE_FLAG] = 0;
	return (0);
}
