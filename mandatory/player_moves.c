/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/20 17:18:00 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_barriers(t_data *data, float x, float y)
{
	int	new_x;
	int	new_y;

	new_x = data->player.player_x + x;
	new_y = data->player.player_y + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + 4 + x;
	new_y = data->player.player_y + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + x;
	new_y = data->player.player_y + 4 + y;
	if (get_color(data, new_x, new_y))
		return (1);
	new_x = data->player.player_x + 4 + x;
	new_y = data->player.player_y + 4 + y;
	if (get_color(data, new_x, new_y))
		return (1);
	return (0);
}

void	w_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;

	if (data->keys[2])
	{
		delta_x = cos(data->player.angle) * SPEED;
		delta_y = sin(data->player.angle) * SPEED;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->player.x_c += delta_x;
		data->player.y_c += delta_y;
	}
}

void	s_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;

	if (data->keys[3])
	{
		delta_x = (cos(data->player.angle) * SPEED) * -1;
		delta_y = (sin(data->player.angle) * SPEED) * -1;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.player_x += delta_x;
		data->player.player_y += delta_y;
		data->player.x_c += delta_x;
		data->player.y_c += delta_y;
	}
}

void	d_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;

	if (data->keys[4])
	{	
		delta_x = sin(data->player.angle) * SPEED;
		delta_y = cos(data->player.angle) * SPEED;
		if (check_barriers(data, -delta_x, delta_y))
			return ;
		data->player.player_x -= delta_x;
		data->player.player_y += delta_y;
		data->player.x_c -= delta_x;
		data->player.y_c += delta_y;
	}
}

void	a_moves(t_data *data)
{
	double	delta_x;
	double	delta_y;

	if (data->keys[5])
	{	
		delta_x = (sin(data->player.angle) * SPEED) * -1;
		delta_y = (cos(data->player.angle) * SPEED) * -1;
		if (check_barriers(data, -delta_x, delta_y))
			return ;
		data->player.player_x -= delta_x;
		data->player.player_y += delta_y;
		data->player.x_c -= delta_x;
		data->player.y_c += delta_y;
	}
}

void	move_player(t_data *data)
{
	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	mlx_put_image_to_window(data->mlx, data->win, data->player.erase_img,
		data->player.player_x, data->player.player_y);
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
}
