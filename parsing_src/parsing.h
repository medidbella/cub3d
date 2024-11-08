/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:30 by midbella          #+#    #+#             */
/*   Updated: 2024/11/07 18:25:05 by midbella         ###   ########.fr       */
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

#define FLOOR 1
#define CEILING 0

typedef struct s_config
{
	char			*NO_texture_path;
	char			*SO_texture_path;
	char			*WE_texture_path;
	char			*EA_texture_path;
	char			*tab[4];
	char			**map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				player_start_angle;
} t_config;

char		*read_line(int fd);
void		file_parser(t_config *scene, char *scene_descrption);
void		data_init(t_config *data);
int			strings_len(char **words);
void		error_handler(char *err, char **free_me, char *me_too);
int			is_map_line(char *str);
char		*ft__strdup(char *str);
void		strings_free(char **strings);

#endif