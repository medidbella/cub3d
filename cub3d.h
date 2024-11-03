/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:21:18 by alaktari          #+#    #+#             */
/*   Updated: 2024/11/03 11:03:38 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx/mlx.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 30
//arrows
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
//keys
#define W 119
#define A 97
#define S 115
#define D 100
#define KeyPressMask 1L<<0
#define KeyPress 2


typedef struct s_player
{
	void	*player_img;
	void	*erase_img;
	int		player_x;
	int		player_y;
	int		size_x;
	int		size_y;
	int		mov_speed;
} t_player;

typedef struct s_data
{
	int			w_size_x;
	int			w_size_y;
	void		*wall;
	void		*ptr;
	void		*win;
	char		**map;
	t_player	*player;
} t_data;

#endif