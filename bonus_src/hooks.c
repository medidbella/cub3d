/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:26:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	check_keys(t_data *data)
{
	if (data->weapons[data->used_weapon].current_frame_index != 0)
		return (true);
	if (!data->keys[MOVE_FLAG] && !data->keys[RIGHT_FLAG]
		&& !data->keys[LEFT_FLAG] && !data->keys[CLOSE_FLAG]
		&& !data->keys[MOUSE_FLAG] && !data->keys[SWITCH_FLAG]
		&& !data->keys[SHOOT_FLAG] && data->keys[OPEN_DOOR] != 1)
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
	if (data->player.angle > 360)
		data->player.angle -= 360;
	else if (data->player.angle < 0)
		data->player.angle += 360;
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
		open_and_close_door(data);
	if (data->keys[CLOSE_FLAG])
		close_win(data);
	if (data->keys[MOUSE_FLAG] || data->keys[RIGHT_FLAG]
		|| data->keys[LEFT_FLAG])
		rotate(data);
	move_player(data);
	if (!check_keys(data))
		return (0);
	ray_casting(data);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	data->keys[MOUSE_FLAG] = 0;
	data->keys[OPEN_DOOR] = 0;
	data->keys[MOVE_FLAG] = 0;
	set_frame_index(data);
	render_weapon(data, &data->weapons[data->used_weapon],
		data->weapons[data->used_weapon].current_frame_index);
	return (0);
}
