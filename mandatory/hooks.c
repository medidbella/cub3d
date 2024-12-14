/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/12/14 15:12:00 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

int	check_keys(t_data *data)
{
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG] && !data->keys[W_FLAG]
		&& !data->keys[S_FLAG] && !data->keys[D_FLAG] && !data->keys[A_FLAG]
		&& !data->keys[CLOSE_FLAG])
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
	return (0);
}
