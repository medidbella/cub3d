#include <mlx.h>
#include <stdio.h>

typedef struct s_texture
{
	void	*img;
	char	*iter;
	int		pixel_bits;
	int		endianess;
	int		line_lenght;
	int		width;
	int		hight;
}	t_texture;

# define WINDOW 150

int get_cords_color(t_texture *img, int x, int y)
{
	char *dst;

	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
	return (*(int *)dst);
}

int main()
{
	t_texture test;

	void *mlx = mlx_init();
	test.img = mlx_xpm_file_to_image(mlx, "../textures/red.xpm", &test.width, &test.hight);
	printf("width = %d\nhight = %d\n", test.width, test.hight);
	void *win = mlx_new_window(mlx, WINDOW, WINDOW, "image");
	test.iter = mlx_get_data_addr(test.img, &test.pixel_bits, &test.line_lenght, &test.endianess);
	int x = 0, y = 0;
	float x_scale = (float)test.width / WINDOW;
	float y_scale = (float)test.hight / WINDOW;
	while (y <= WINDOW)
	{
		x = 0;
		while (x <= WINDOW)
		{
			mlx_pixel_put(mlx, win, x, y, get_cords_color(&test,
				x_scale * x, y_scale * y));
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}