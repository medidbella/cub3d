/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/18 19:09:37 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 
  
// DDA Function for line generation 
void DDA(int X0, int Y0, int X1, int Y1, int color, t_data *data)
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
        my_mlx_pixel_put(data, round(X), round(Y), color); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        // delay(100); // for visualization of line- 
                    // generation step by step 
    } 
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
    {
        return ;
    }
    dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put_2d(t_data *data, int x, int y, int color)
{
	char	*dst;

    if (x <= 0 || x >= WIDTH_2D || y <= 0 || y >= HEIGHT_2D)
        return ;
    // printf("x: %d || y: %d\n", x, y);
    // exit (0);
	dst = data->img_2d.addr + (y * data->img_2d.line_length + x * (data->img_2d.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_cub(t_data *data, int x, int y, int color)
{
    int x_ = x;
    int y_ = y;
    while (y < y_ + TILE_SIZE)
    {
        x = x_;
        // printf("--> %d\n", (y_ + TILE_SIZE));exit (0);
        while (x < x_ + TILE_SIZE)
        {
            my_mlx_pixel_put_2d(data, x, y, color);
            x++;
        }
        y++;
    }
    // printf("x : %d || y : %d\n", x, y);exit (0);
}

void draw(t_data *data)
{
    int i, j, x, y, color;

    i = 0, j = 0, x = 0, y = 0;
    while (data->map[i])
    {
        j = 0;
        y = i * TILE_SIZE;
        while (data->map[i][j])
        {
            color = BLACK;
            x = j * TILE_SIZE;
            if (data->map[i][j] == '1')
                color = WALL_COLOR;
            else if (data->map[i][j] == '0')
                color = BLACK;
            if (ft_strchr("NSWE", data->map[i][j])&& data->player.player == 0)
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
    // printf("j : %d || i : %d\n", j, i);exit (0);

}

void draw_direction(t_data *data, int color)
{
    bresenham(data->player.x_c, data->player.y_c, data->player.x_direction, data->player.y_direction, color, data); 
}

void    setup(t_data *data)
{
    data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    
    data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bits_per_pixel),
			&(data->img.line_length), &(data->img.endian));

    data->img_2d.img = mlx_new_image(data->mlx, WIDTH_2D, HEIGHT_2D);
    data->img_2d.addr = mlx_get_data_addr(data->img_2d.img, &(data->img_2d.bits_per_pixel),
            &(data->img_2d.line_length), &(data->img_2d.endian));

    data->player.player_img = mlx_xpm_file_to_image(data->mlx,
		"textures/mini_player.xpm", &(data->player.size_x), &(data->player.size_y));

    data->player.erase_img = mlx_xpm_file_to_image(data->mlx,
		"textures/erase.xpm", &(data->player.size_x), &(data->player.size_y));

	draw(data);
   
    // printf("first coordinates x: %d || y: %d\n", data->player.player_x, data->player.player_y);
    data->player.x_c = data->player.player_x + (data->player.size_x / 2);
	data->player.y_c = data->player.player_y + (data->player.size_y / 2);

    
    data->player.x_direction = data->player.x_c + DIRECTION;
    data->player.y_direction = data->player.y_c;

    data->player.fov = FOV;
    data->player.angle_step = (data->player.fov / WIDTH);
    data->player.distance_to_project_plan = ((float)WIDTH / 2) * tan(radian((float)FOV / 2));
    draw_direction(data, DIR_COLOR);
}

void get_start(t_config *parsed_data)//, int ceiling, int floor)
{
    t_data  data;

    data.map = parsed_data->map;
    data.player.player = 0;
    data.player.angle = parsed_data->player_start_angle;
    data.ceiling_color = parsed_data->ceiling_color;
    data.floor_color = parsed_data->floor_color;
	setup(&data);
    printf("W: %d || H: %d\n", WIDTH_2D, WIDTH_2D);
    printf("x_c : %f || y_c : %f || angle: %f\n", data.player.x_c, data.player.y_c, data.player.angle);
        
    // data.player.angle = 20;
    // rotate(&data, LEFT);
    // printf("playerangle: %f\n", data.player.angle);
    // printf("==========================================\n\n");
    
    ray_casting(&data);
    // printf("here\n");
    
    mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
    mlx_put_image_to_window(data.mlx, data.win, data.img_2d.img, 0, 0);
    mlx_put_image_to_window(data.mlx, data.win, data.player.player_img,
				data.player.player_x, data.player.player_y);

	mlx_hook(data.win, 2, 1L << 0, hooks, &data);
	mlx_hook(data.win, 17, 1L << 2, close_win1, &data);
	mlx_loop(data.mlx);

}
