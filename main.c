/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:22:27 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/03 09:59:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_map(char **map, t_data *mlx)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->wall,
				j * SIZE, i * SIZE);	
			else if (map[i][j] == 'P')
			{
				mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->player->player_img,
					j * SIZE + 10, i * SIZE + 10);
				mlx->player->player_x = j * SIZE + 10;
				mlx->player->player_y = i * SIZE + 10;
			}
			j++;
		}
		i++;
	}
}

void	change_cords(t_player *player, int key)
{
	if (key == W)
		player->player_y -= player->mov_speed;
	else if (key == S)
		player->player_y += player->mov_speed;
	else if (key == A)
		player->player_x -= player->mov_speed;
	else if (key == D)
		player->player_x += player->mov_speed;

}

void	move_player(int key, t_data *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->player->erase_img,
		mlx->player->player_x, mlx->player->player_y);
	change_cords(mlx->player, key);
	change_cords(mlx->player, key);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->player->player_img,
		mlx->player->player_x, mlx->player->player_y);
}

int	keyboard_handler(int key, t_data *mlx) 
{
	if (key == W || key == A || key == S || key == D)
		move_player(key, mlx);
	return (1);
}

int main()
{
	t_data		mlx;
	t_player	player;

	player.mov_speed = 1;
	char *tab[] = {
					"111111111111",
					"100000000001",
					"100000010001",
					"100000000001",
					"101P00000001",
					"111111111111",
					NULL
	};
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 12 * SIZE, 6 * SIZE, "none");
	mlx.player = &player;
	player.erase_img = mlx_xpm_file_to_image(mlx.ptr,
		"textures/erase.xpm", &player.size_x, &player.size_y);
	player.player_img = mlx_xpm_file_to_image(mlx.ptr,
		"textures/mini_player.xpm", &player.size_x, &player.size_y);
	mlx.wall = mlx_xpm_file_to_image(mlx.ptr, "textures/wall.xpm",
		&mlx.w_size_x, &mlx.w_size_y);
	render_map(tab, &mlx);
	mlx_key_hook(mlx.win, keyboard_handler, &mlx);
	mlx_loop(mlx.ptr);
}
