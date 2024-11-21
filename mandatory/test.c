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

// int get_cords_color(t_texture *img, int x, int y)
// {
// 	char *dst;

// 	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
// 	return ((unsigned int )*dst);
// }

int get_cords_color(t_texture *img, int x, int y) {
	char	*dst;
	int		color;

	dst = img->iter + (y * img->line_lenght + x * (img->pixel_bits / 8));
	if (img->pixel_bits == 32)
		color = *(int *)dst; // 32-bit color (RGBA)
	else if (img->pixel_bits == 24)
		color = *(int *)dst & 0xFFFFFF; // 24-bit color (RGB)
	else
		color = *(unsigned char *)dst; // Grayscale or indexed color
	return (img->endianess == 1) ? __builtin_bswap32(color) : color;
}

int main()
{
	t_texture test;

	void *mlx = mlx_init();
	test.img = mlx_xpm_file_to_image(mlx, "../textures/red.xpm", &test.width, &test.hight);
	printf("width = %d\nhight = %d\n", test.width, test.hight);
	void *win = mlx_new_window(mlx, test.width, test.hight, "image");
	test.iter = mlx_get_data_addr(test.img, &test.pixel_bits, &test.line_lenght, &test.endianess);
	int x = 0, y = 0;
	while (y <= test.hight)
	{
		x = 0;
		while (x <= test.width)
		{
			mlx_pixel_put(mlx, win, x, y, get_cords_color(&test, x, y));
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}