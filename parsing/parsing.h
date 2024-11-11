/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:30 by midbella          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:39 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARS_H
#define PARS_H

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include <errno.h>

#define CEILING 0

#define E_ANGLE 0
#define N_ANGLE 90
#define W_ANGLE 180
#define S_ANGLE 270

typedef struct s_config
{
	char			*NO_texture_path;
	char			*SO_texture_path;
	char			*WE_texture_path;
	char			*EA_texture_path;
	char			*tab[4];
	char			**map;
	int				floor_color;
	int				ceiling_color;
	int				player_start_angle;
} t_config;

char		*read_line(int fd);
void		file_parser(t_config *scene, char *scene_descrption);
void		data_init(t_config *data);
int			strings_len(char **words);
void		error_handler(char *err, char **free_me, char *me_too,
				t_config *data);
int			is_map_line(char *str);
char		*ft__strdup(char *str);
void		strings_free(char **strings);
char		**map_alloc(char *line, int fd, t_config *scene_data);
void		free_parsed_data(t_config *data);
int			top_bottom_check(char *str);
void		map_parser(char **map, t_config *scene_data);
int			check_prev_members(t_config *scene_data);
void		print_config(t_config *data);//temp
int			open_cub_file(char *file);

#endif