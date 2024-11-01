#include <mlx.h>
#include <unistd.h>
#include <string.h>
#define S 30

int main()
{
	int x;
	int y;
	int i;
	int j;
	char *tab[] = {
					"111111111111",
					"100000000001",
					"100000010001",
					"100000000001",
					"100P00000001",
					"111111111111",
					NULL};
	
	x = 0;
	i = 0;
	j = 0;
	y = 0;
	void *mlx_ptr = mlx_init();
	void *mlx_win = mlx_new_window(mlx_ptr, 12 * S, 6 * S, "none");
	while (tab[i])
	{
		x = 0;
		while()
		{
			
		}
	}
	mlx_loop(mlx_ptr);
}
