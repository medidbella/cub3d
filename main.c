#include "mlx.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define S 30

typedef struct s_player
{
	void	*player_img;
	int		player_x;
	int		player_y;
	int		size_x;
	int		size_y;
	int		mov_speed;
} t_player;

typedef struct s_data
{
	void		*ptr;
	void		*win;
	t_player	*player;
} t_data;

void render_wall(int x, int y, t_data *mlx)
{
	int temp_x = x;
	int temp_y = y;

	while (y <= temp_y + S)
	{
		x = temp_x;
		while (x <= temp_x + S)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, x, y, 0xffffff);
			x++;
		}
		y++;
	}
}

void render_map(char **map, t_data *mlx)
{
	int x;
	int y;
	int i;
	int j;

	x = 0;
	i = 0;
	j = 0;
	y = 0;

	while (map[i])
	{
		x = 0;
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				render_wall(x, y, mlx);
			x += S;
			j++;
		}
		y += S;
		i++;
	}
}

void put_player(char **map, t_data *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->player->player_img,
					j * S + 10, i * S + 10);
				mlx->player->player_x = j * S + 10;
				mlx->player->player_y = i * S + 10;
			}
			j++;
		}
		i++;
	}
}

// int	keyboard_handler(void) 
// {

// }

int main()
{
	t_data		mlx;
	t_player	player;

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
	mlx.win = mlx_new_window(mlx.ptr, 12 * S, 6 * S, "none");
	mlx.player = &player;
	player.player_img = mlx_xpm_file_to_image(mlx.ptr,
		"textures/mini_player.xpm", &player.size_x, &player.size_y);
	render_map(tab, &mlx);
	put_player(tab, &mlx);
	mlx_key_hook(mlx.win, );
	mlx_loop(mlx.ptr);
}
