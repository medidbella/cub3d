/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/19 13:50:42 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_key_flags(t_data *data)
{
	data->keys[RIGHT_FLAG] = false;
	data->keys[LEFT_FLAG] = false;
	data->keys[W_FLAG] = false;
	data->keys[S_FLAG] = false;
	data->keys[D_FLAG] = false;
	data->keys[A_FLAG] = false;
	data->keys[CLOSE_FLAG] = false;
	data->keys[ROTATE_FLAG] = false;
	data->keys[MOVE_FLAG] = false;
}

int	ft_key_press(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = true;
	if (key == LEFT)
		data->keys[LEFT_FLAG] = true;
	if (key == W)
		data->keys[W_FLAG] = true;
	if (key == S)
		data->keys[S_FLAG] = true;
	if (key == D)
		data->keys[D_FLAG] = true;
	if (key == A)
		data->keys[A_FLAG] = true;
	if (key == CLOSE)
		data->keys[CLOSE_FLAG] = true;
	return (false);
}

int	ft_key_release(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = false;
	if (key == LEFT)
		data->keys[LEFT_FLAG] = false;
	if (key == W)
		data->keys[W_FLAG] = false;
	if (key == S)
		data->keys[S_FLAG] = false;
	if (key == D)
		data->keys[D_FLAG] = false;
	if (key == A)
		data->keys[A_FLAG] = false;
	return (0);
}
