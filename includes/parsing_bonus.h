/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:30 by midbella          #+#    #+#             */
/*   Updated: 2024/12/22 13:25:01 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define CEILING 0
# define E_ANGLE 0
# define N_ANGLE 270
# define W_ANGLE 180
# define S_ANGLE 90
# define DOOR_IDX 4

typedef struct s_config
{
	char			*textures_paths[5];
	char			**map;
	int				door_flag;
	int				floor_color;
	int				map_width;
	int				map_hight;
	int				ceiling_color;
	int				player_start_angle;
}	t_config;

void		set_hight_width(t_config *scene_data);
char		*read_line(int fd);
void		file_parser(t_config *scene, char *scene_description);
void		data_init(t_config *data);
int			strings_len(char **words);
void		error_handler(char *err, char **free_me, char *me_too,
				t_config *data);
int			is_map_line(char *str);
void		strings_free(char **strings);
char		**map_alloc(char *line, int fd, t_config *scene_data);
void		free_parsed_data(t_config *data);
int			top_bottom_check(char *str);
void		ft_access(char *file, t_config *scene_data, char *line, int i);
void		map_parser(char **map, t_config *scene_data);
void		check_prev_members(t_config *scene_data, char *line);
int			open_cub_file(char *file);
void		get_textures(char **words, t_config *scene_data, char *line);
void		color_parser(t_config *scene_data, char *line, int type);
void		alignment_check(char **map, int x, int y, t_config *scene_data);
void		switch_doors(char **map);

#endif