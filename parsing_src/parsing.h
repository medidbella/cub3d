/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:30 by midbella          #+#    #+#             */
/*   Updated: 2024/11/06 16:02:28 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARS_H
#define PARS_H

#include "../cub.h"
#include <errno.h>

typedef struct s_config
{
	char			*NO_texture_path;
	char			*SO_texture_path;
	char			*WE_texture_path;
	char			*EA_texture_path;
	char			**map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				player_start_angle;
} t_config;

char		*read_line(int fd);
int			file_parser(t_config *scene, char *scene_descrption);
static void	data_init(t_config *data);
int			strings_len(char **words);
void		error_handl(char *err);
int			is_map_line(char *str);
int			is_element(char *str);

#endif