#include "./mandatory/cub3d.h"

void fill_win(t_data *data)
{
	int x = 0;
	int y = 0;

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int mouse_handler(int x, int y, t_data *data)
{
	int delta_x;
	int delta_y;

	mlx_mouse_hide(data->mlx, data->win);
	delta_x = x - (WIDTH / 2);
	delta_y = y - (HEIGHT / 2);
	if (delta_x || delta_y)
	{
		data->mouse_x += delta_x;
		data->mouse_y += delta_y;
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	}
	printf("x_mouse: %d || y_mouse: %d\n", data->mouse_x, data->mouse_y);
	return (0);
}

int main()
{
	t_data data;

	data.mouse_x = 0;
	data.mouse_y = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "test");
	fill_win(&data);
	mlx_hook(data.win, 6, 1L << 6, mouse_handler, &data);
	mlx_hook(data.win, 17, 1L << 2, close_win, &data);
	mlx_hook(data.win, 2, 1L << 0, close_win, &data);
	mlx_loop(data.mlx);
}