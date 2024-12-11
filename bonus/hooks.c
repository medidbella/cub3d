/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/11 18:24:25 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_keys(t_data *data)
{
	if (data->weapons[data->used_weapon].current_frame_index != 0)
		return (true);
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG] && !data->keys[W_FLAG]
		&& !data->keys[S_FLAG] && !data->keys[D_FLAG] && !data->keys[A_FLAG]
		&& !data->keys[CLOSE_FLAG] && !data->keys[MOUSE_FLAG]
		&& !data->keys[SWITCH_FLAG] && !data->keys[SHOOT_FLAG]
		&& !data->keys[OPEN_DOOR])
		return (false);
	return (true);
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
	if (data->keys[OPEN_DOOR])
		open_door(data);
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

	// printf("Px: %f || Py: %f || angle: %f\n", data->player.player_x, data->player.player_y, data->player.angle);
	
	return (0);
}
