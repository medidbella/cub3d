/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:01:34 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_data *data)
{
	if (!data->keys[0] && !data->keys[1])
		return ;
	if (data->keys[0])
	{
		data->player.angle += radian(ANGLE);
		if (data->player.angle >= radian(360))
			data->player.angle -= radian(360);
	}
	if (data->keys[1])
	{
		data->player.angle -= radian(ANGLE);
		if (data->player.angle < 0)
			data->player.angle = radian(355);
	}
}
