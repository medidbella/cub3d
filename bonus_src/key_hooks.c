/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/22 18:20:42 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_key_flags(t_data *data)
{
	data->keys[RIGHT_FLAG] = false;
	data->keys[LEFT_FLAG] = false;
	data->keys[MOVE_FLAG] = false;
	data->keys[W_FLAG] = false;
	data->keys[S_FLAG] = false;
	data->keys[D_FLAG] = false;
	data->keys[A_FLAG] = false;
	data->keys[CLOSE_FLAG] = false;
	data->keys[MOUSE_FLAG] = false;
	data->keys[SWITCH_FLAG] = false;
	data->keys[SHOOT_FLAG] = false;
	data->keys[OPEN_DOOR] = false;
}

int	ft_key_press(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = true;
	else if (key == LEFT)
		data->keys[LEFT_FLAG] = true;
	else if (key == W)
		data->keys[W_FLAG] = true;
	else if (key == S)
		data->keys[S_FLAG] = true;
	else if (key == D)
		data->keys[D_FLAG] = true;
	else if (key == A)
		data->keys[A_FLAG] = true;
	else if (key == CLOSE)
		data->keys[CLOSE_FLAG] = true;
	else if (key == CHANGE_WEAPON)
		data->keys[SWITCH_FLAG] = true;
	else if (key == SHOOT_BUTTON)
		data->keys[SHOOT_FLAG] = true;
	else if (key == OPEN)
		data->keys[OPEN_DOOR] = true;
	return (false);
}

int	ft_key_release(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = false;
	else if (key == LEFT)
		data->keys[LEFT_FLAG] = false;
	else if (key == W)
		data->keys[W_FLAG] = false;
	else if (key == S)
		data->keys[S_FLAG] = false;
	else if (key == D)
		data->keys[D_FLAG] = false;
	else if (key == A)
		data->keys[A_FLAG] = false;
	else if (key == SHOOT_BUTTON)
		data->keys[SHOOT_FLAG] = false;
	else if (key == CHANGE_WEAPON)
		data->keys[SWITCH_FLAG] = false;
	else if (key == OPEN)
		data->keys[OPEN_DOOR] = false;
	return (0);
}

int	ft_mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = param;
	if (data->use_mouse == false)
		return (0);
	if (button == 1)
		data->keys[SHOOT_FLAG] = true;
	else if (button == 4)
		weapon_switch(data, 1);
	else if (button == 5)
		weapon_switch(data, -1);
	else if (button == 3)
	{
		data->use_mouse = false;
		mlx_mouse_show(data->mlx, data->win);
	}
	return (0);
}

int	ft_mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = param;
	if (data->use_mouse == false)
		return (0);
	if (button == 1)
		data->keys[SHOOT_FLAG] = false;
	return (0);
}
