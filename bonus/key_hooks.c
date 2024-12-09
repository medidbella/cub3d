/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/06 16:28:14 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_key_flags(t_data *data)
{
	data->keys[RIGHT_FLAG] = 0;
	data->keys[LEFT_FLAG] = 0;
	data->keys[W_FLAG] = 0;
	data->keys[S_FLAG] = 0;
	data->keys[D_FLAG] = 0;
	data->keys[A_FLAG] = 0;
	data->keys[CLOSE_FLAG] = 0;
	data->keys[MOUSE_FLAG] = 0;
	data->keys[SWITCH_FLAG] = 0;
	data->keys[SHOOT_FLAG] = 0;
}

int	ft_key_press(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[0] = (key == RIGHT);
	if (key == LEFT)
		data->keys[LEFT_FLAG] = 1;
	if (key == W)
		data->keys[W_FLAG] = 1;
	if (key == S)
		data->keys[S_FLAG] = 1;
	if (key == D)
		data->keys[D_FLAG] = 1;
	if (key == A)
		data->keys[A_FLAG] = 1;
	if (key == CLOSE)
		data->keys[CLOSE_FLAG] = 1;
	if (key == CHANGE_WEAPON)
		data->keys[SWITCH_FLAG] = 1;
	if (key == SHOOT_BUTTON)
		data->keys[SHOOT_FLAG] = 1;
	return (0);
}

int	ft_key_release(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = 0;
	if (key == LEFT)
		data->keys[LEFT_FLAG] = 0;
	if (key == W)
		data->keys[W_FLAG] = 0;
	if (key == S)
		data->keys[S_FLAG] = 0;
	if (key == D)
		data->keys[D_FLAG] = 0;
	if (key == A)
		data->keys[A_FLAG] = 0;
	if (key == SHOOT_BUTTON)
		data->keys[SHOOT_FLAG] = 0;
	if (key == CHANGE_WEAPON)
		data->keys[SWITCH_FLAG] = 0;
	return (0);
}

int	ft_mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = param;
	if (button == 1)
		data->keys[SHOOT_FLAG] = 1;
	else if (button == 4)
		weapon_switch(data, 1);
	else if (button == 5)
		weapon_switch(data, -1);
	return (0);
}

int	ft_mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = param;
	if (button == 1)
		data->keys[SHOOT_FLAG] = 0;
	return (0);
}
