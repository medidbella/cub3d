/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:06:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_key_flags(t_data *data)
{
	data->keys[RIGHT_FLAG] = 0;
	data->keys[LEFT_FLAG] = 0;
	data->keys[W_FLAG] = 0;
	data->keys[S_FLAG] = 0;
	data->keys[D_FLAG] = 0;
	data->keys[A_FLAG] = 0;
	data->keys[CLOSE_FLAG] = 0;
	data->keys[ROTATE_FLAG] = 0;
	data->keys[MOVE_FLAG] = 0;
}

int	ft_key_press(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[RIGHT_FLAG] = 1;
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
	return (0);
}
