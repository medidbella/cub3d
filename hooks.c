/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:35:28 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/05 14:09:56 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_win1(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(0);
}

int  get_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return 0;
	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	return (*(unsigned int *) dst == 0x61F5B5);
}

static int ft_barriers(t_data *data, int key)
{
	int new_x1, new_x2;
	int new_y1, new_y2;

	new_y1 = data->player.player_y;
	new_x1 = data->player.player_x;

	if (key == W || key == S)
	{
		new_x2 = new_x1 + 4;
		if (key == W)
		{
			new_y1 = data->player.player_y - SPEED;
			new_y2 = new_y1;
		}
		else
		{
			new_y1 = data->player.player_y + SPEED + IMG_SIZE_Y;
        	new_y2 = new_y1;
		}
	}
	else if (key == A || key == D)
	{
		new_y2 = new_y1 + 4;
		if (key == A)
		{
			new_x1 = data->player.player_x - SPEED;
			new_x2 = new_x1;
		}
		else
		{
			new_x1 = data->player.player_x + SPEED + IMG_SIZE_X;
			new_x2 += new_x1;
		}
	}
	return (get_color(data, new_x1, new_y1) || get_color(data, new_x2, new_y2));
}

void draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->player.player_img,
				data->player.player_x, data->player.player_y);
}

void move_player(t_data *data, int key)
{
	if (ft_barriers(data, key))
		return ;
	mlx_put_image_to_window(data->mlx, data->win, data->player.erase_img,
				data->player.player_x, data->player.player_y);
	if (key == W)
		data->player.player_y -= SPEED;
	else if (key == S)
		data->player.player_y += SPEED;
	else if (key == D)
		data->player.player_x += SPEED;
	else if (key == A)
		data->player.player_x -= SPEED;
}

int hooks(int key, t_data *data)
{
	if (key == 32)
		close_win1(data);
	if (key != W && key != S && key != A && key != D)
		return 0;
	move_player(data, key);
	draw_player(data);

}