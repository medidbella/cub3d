/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/28 14:37:44 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_textures_memory(data->mlx, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_image(data->mlx, data->player.erase_img);
	mlx_destroy_image(data->mlx, data->player.player_img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	move_player(t_data *data)
{
	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
	data->player.mini_x = data->player.x_c
		* data->scale - (data->mini_width / 2);
	data->player.mini_y = data->player.y_c
		* data->scale - (data->mini_height / 2);
}

int	check_keys(t_data *data)
{
	if (!data->keys[0] && !data->keys[1] && !data->keys[2]
		&& !data->keys[3] && !data->keys[4] && !data->keys[5]
		&& !data->keys[6])
		return (0);
	return (1);
}

int	loop_rendering(t_data *data)
{
	if (!check_keys(data))
		return (0);
	if (data->keys[6])
		close_win(data);
	rotate(data);
	move_player(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw(data);
	draw_player(data);
	return (0);
}
