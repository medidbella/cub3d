/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/19 13:19:20 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_data *data)
{
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG])
		return ;
	if (data->keys[RIGHT_FLAG])
	{
		data->player.angle += ANGLE;
		if (data->player.angle >= 360)
			data->player.angle -= 360;
	}
	if (data->keys[LEFT_FLAG])
	{
		data->player.angle -= ANGLE;
		if (data->player.angle < 0)
			data->player.angle += 360;
	}
}
