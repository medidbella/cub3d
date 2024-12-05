/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/05 10:48:38 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_wall_textures_memory(data, data->wall_textures);
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
	float	tab[2];

	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data, tab);
	s_moves(data, tab);
	d_moves(data, tab);
	a_moves(data, tab);
	data->player.player_x += tab[0];
	data->player.player_y += tab[1];
	data->player.mini_x = data->player.player_x
		* data->scale - (data->mini_width / 2);
	data->player.mini_y = data->player.player_y
		* data->scale - (data->mini_height / 2);
}

int	check_keys(t_data *data)
{
	if (data->weapons[data->used_weapon].current_frame_index != 0)
		return (1);
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG] && !data->keys[W_FLAG]
		&& !data->keys[S_FLAG] && !data->keys[D_FLAG] && !data->keys[A_FLAG]
		&& !data->keys[CLOSE_FLAG] && !data->keys[MOUSE_FLAG]
		&& !data->keys[SWITCH_FLAG] && !data->keys[SHOOT_FLAG])
		return (0);
	return (1);
}

void	mouse_events(t_data *data)
{
	int	x;
	int	y;
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
	if (data->keys[SWITCH_FLAG])
		weapon_switch(data, 1);
	if (data->keys[SHOOT_FLAG])
		start_animation(data);
	if (!check_keys(data))
		return (0);
	if (data->keys[CLOSE_FLAG])
		close_win(data);
	rotate(data);
	move_player(data);
	ray_casting(data);
	draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_player(data);
	data->keys[MOUSE_FLAG] = 0;
	set_frame_index(data);
	render_weapon(data, &data->weapons[data->used_weapon],
		data->weapons[data->used_weapon].current_frame_index);
	return (0);
}
