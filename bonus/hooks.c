/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/24 17:19:58 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_textures_memory(data->mlx, data->wall_textures);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_image(data->mlx, data->img_2d.img);
	mlx_destroy_image(data->mlx, data->player.erase_img);
	mlx_destroy_image(data->mlx, data->player.player_img);
	mlx_destroy_window(data->mlx, data->win);
	strings_free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	draw_map2d(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
		data->player.player_x, data->player.player_y);
}

void	move_player(t_data *data)
{
	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	// mlx_put_image_to_window(data->mlx, data->win, data->player.erase_img,
	// 	data->player.player_x, data->player.player_y);
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
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
	draw(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	// draw_map2d(data);
	// mlx_put_image_to_window(data->mlx, data->win, data->mini_map_img.img, 0, 0);
	return (0);
}
