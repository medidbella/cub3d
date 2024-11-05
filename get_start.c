#include "cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_cub(t_data *data, int x, int y, int color)
{
    int x_ = x;
    int y_ = y;
    while (y < y_ + TILE_SIZE)
    {
        x = x_;
        while (x < x_ + TILE_SIZE)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

void draw(t_data *data)
{
    int i, j, x, y, color;

    i = 0, j = 0, x = 0, y = 0;
    while (i < ROWS)
    {
        j = 0;
        y = i * TILE_SIZE;
        while (j < COLS)
        {
            color = 0x000000;
            x = j * TILE_SIZE;
            if (data->map[i][j] == '1')
                color = 0x61F5B5;
            else if (data->map[i][j] == '0')
                color = 0x000000;
            if (data->map[i][j] == 'P' && data->player.player == 0)
            {
                data->player.player = 1;
                data->player.player_x = j * TILE_SIZE + TILE_SIZE / 2;
                data->player.player_y = i * TILE_SIZE + TILE_SIZE / 2;
            }
            draw_cub(data, x, y, color);
            j++;
        }
        i++;
    }
}

void setup(t_data *data)
{
    data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "none");
    data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bits_per_pixel),
			&(data->img.line_length), &(data->img.endian));

    data->player.player_img = mlx_xpm_file_to_image(data->mlx,
		"textures/mini_player.xpm", &(data->player.size_x), &(data->player.size_y));

    data->player.erase_img = mlx_xpm_file_to_image(data->mlx,
		"textures/erase.xpm", &(data->player.size_x), &(data->player.size_y));

	data->player.x_c = data->player.size_x / 2;
	data->player.y_c = data->player.size_y / 2; 
    
}

void get_start(char **map)
{
	t_data data;
	data.map = map;
	data.player.player = 0;
	setup(&data);
	draw(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.player.player_img,
				data.player.player_x, data.player.player_y);
	mlx_hook(data.win, 2, 1L << 0, hooks, &data);
	mlx_hook(data.win, 17, 1L << 2, close_win1, &data);
	mlx_loop(data.mlx);

}
