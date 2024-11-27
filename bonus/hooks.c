/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/27 19:39:55 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_textures_memory(data, data->wall_textures);
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
	float	tab[2];

	if (!data->keys[2] && !data->keys[3] && !data->keys[4] && !data->keys[5])
		return ;
	w_moves(data, tab);
	s_moves(data, tab);
	d_moves(data, tab);
	a_moves(data, tab);
	data->player.player_x += tab[0];
	data->player.player_y += tab[1];
	data->player.x_c += tab[0];
	data->player.y_c += tab[1];
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
	draw_map2d(data);
	return (0);
}
