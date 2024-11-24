/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:14 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 12:32:47 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_key_flags(t_data *data)
{
	data->keys[0] = 0;
	data->keys[1] = 0;
	data->keys[2] = 0;
	data->keys[3] = 0;
	data->keys[4] = 0;
	data->keys[5] = 0;
	data->keys[6] = 0;
}

int	ft_key_press(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[0] = 1;
	if (key == LEFT)
		data->keys[1] = 1;
	if (key == W)
		data->keys[2] = 1;
	if (key == S)
		data->keys[3] = 1;
	if (key == D)
		data->keys[4] = 1;
	if (key == A)
		data->keys[5] = 1;
	if (key == CLOSE)
		data->keys[6] = 1;
	return (0);
}

int	ft_key_release(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys[0] = 0;
	if (key == LEFT)
		data->keys[1] = 0;
	if (key == W)
		data->keys[2] = 0;
	if (key == S)
		data->keys[3] = 0;
	if (key == D)
		data->keys[4] = 0;
	if (key == A)
		data->keys[5] = 0;
	return (0);
}
