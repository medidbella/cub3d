/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:01:23 by midbella          #+#    #+#             */
/*   Updated: 2024/11/28 18:28:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pre_init(t_weapon *weapons)
{
	weapons[0].frames_nb = PISTOLE_FNB;
	weapons[1].frames_nb = SHOTGUN_FNB;
	weapons[0].wepoan_frames = malloc(sizeof(t_texture) * weapons[0].frames_nb);
	weapons[1].wepoan_frames = malloc(sizeof(t_texture) * weapons[1].frames_nb);
}

void	sprites_init(t_weapon *weapons, void *mlx)
{
	int		i;
	int		iter;
	char	*tab[WEAPON_NB];

	i = -1;
	tab[0] = ft_strdup("textures/pistole/pist_f1.xpm");
	tab[1] = ft_strdup("textures/shotgun/sgun_f1.xpm");
	pre_init(weapons);
	while (++i < WEAPON_NB)
	{
		iter = -1;
		while (++iter < weapons[i].frames_nb)
		{
			texture_init(mlx, &weapons[i].wepoan_frames[iter], tab[i]);
			tab[i][ft_strlen(tab[i]) - 5]++;
		}
	}
	free(tab[0]);
	free(tab[1]);
}

void	free_sprites_memory(t_weapon *weapons, void *mlx)
{
	int i;
	int iter;

	i = 0;
	while (i < WEAPON_NB)
	{
		iter = 0;
		while (iter < weapons[i].frames_nb)
		{
			mlx_destroy_image(weapons[i].wepoan_frames[iter].img, mlx);
			iter++;
		}
		i++;
	}
	free(weapons->wepoan_frames);
}

void	render_weapon(t_data *data, t_weapon *weapon)
{
	unsigned int	color;
	int				x;
	int				y;
	int			new_width;
	int			new_hight;

	new_width = WIDTH / 4;
	new_hight = HEIGHT / 2;
	weapon->x_scale =  (float)weapon->wepoan_frames[0].width / new_width;
	weapon->y_scale =  (float)weapon->wepoan_frames[0].hight / new_hight;
	weapon->x_start = HEIGHT / 2 + (weapon->wepoan_frames[0].hight / 2);
	x = 0;
	while (x < new_width)
	{
		y = 0;
		weapon->y_start = HEIGHT - new_hight;
		while (y < new_hight)
		{
			color = get_cords_color(&weapon->wepoan_frames[0],
				x * weapon->x_scale, y * weapon->y_scale);
			if (color != 0xff000000)
				mlx_pixel_put(data->mlx, data->win, weapon->x_start,
					weapon->y_start, color);
			weapon->y_start++;
			y++;
		}
		weapon->x_start++;
		x++;
	}
}

//pist x = 110 y = 130