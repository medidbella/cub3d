/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:18:52 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/18 19:27:43 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static float	ft_indexes(t_data *data, float *new_x, float *new_y,
							float *index_x)
{
	float	index_y;

	data->x_added = 0;
	data->y_added = 0;
	if (data->player.player_y < (*new_y) && !data->in_door
		&& (int)(*new_y) % TILE_SIZE != 0)
	{
		(*new_y) += data->speed;
		data->y_added = 1;
	}
	if (data->player.player_x < (*new_x) && !data->in_door
		&& (int)(*new_x) % TILE_SIZE != 0)
	{
		(*new_x) += data->speed;
		data->x_added = 1;
	}
	*index_x = ((*new_x) / TILE_SIZE) - ((int)(*new_x) % TILE_SIZE == 0
			&& ((data->player.player_x > (*new_x) && !data->in_v_door)
				|| (data->in_v_door && data->player.player_x < (*new_x))));
	index_y = ((*new_y) / TILE_SIZE)
		- ((int)(*new_y) % TILE_SIZE == 0
			&& ((data->player.player_y > (*new_y) && !data->in_h_door)
				|| (data->in_h_door && data->player.player_y < (*new_y))));
	return (index_y);
}

int	get_indexes(t_data *data, float *new_x, float *new_y, float *index_x)
{
	float	index_y;

	index_y = ft_indexes(data, new_x, new_y, index_x);
	if (!(!((int)index_y < data->height_2d
				&& (int)index_y >= 0 && (int)(*index_x) >= 0
			&& (int)(*index_x) < (int)ft_strlen(data->map[(int)index_y]))))
	{
		if (ft_strchr("HV", data->map[(int)index_y][(int)(*index_x)]))
		{
			if (data->x_added)
				*new_x -= data->speed;
			if (data->y_added)
				*new_y -= data->speed;
			if (!data->x_added && !data->y_added)
				return (index_y);
			*index_x = ((*new_x) / TILE_SIZE) - ((int)(*new_x) % TILE_SIZE == 0
					&& ((data->player.player_x > (*new_x)) || (data->in_v_door
							&& data->player.player_x < (*new_x))));
			index_y = ((*new_y) / TILE_SIZE) - ((int)(*new_y) % TILE_SIZE == 0
					&& ((data->player.player_y > (*new_y)) || (data->in_h_door
							&& data->player.player_y < (*new_y))));
		}
	}
	return (index_y);
}
