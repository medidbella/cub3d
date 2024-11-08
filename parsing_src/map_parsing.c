/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:44:23 by midbella          #+#    #+#             */
/*   Updated: 2024/11/08 21:50:25 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**map_alloc(char *line, int fd, t_config *scene_data)
{
	int i;
	char	**res;
	char 	*new_line;
	char	*tmp;

	i = 0;
	new_line =  read_line(fd);
	while (new_line)
	{
		tmp = line;
		line = ft_strjoin(line, new_line);
		if (!line)
			return (free(new_line), error_handler
				("insufficient memory\n", NULL, tmp, scene_data), NULL);
		free(tmp);
		free(new_line);
		new_line = read_line(fd);
	}
	res = ft_split(line, '\n');
	if (!res)
		error_handler("insufficient memory\n", NULL, line, scene_data);
	return (free(line), res);
}

void	player_space_border_check(t_config *scene_data, int y, int x)
{
	int flag;
	char **map;

	flag = 0;
	map = scene_data->map;
	if (map[y][x + 1] && map[y][x + 1] != '1' && map[y][x + 1] != ' ')
		flag = 1;
	else if (x > 0 && map[y][x - 1] != '1' && map[y][x - 1] != ' ')
		flag = 1;
	else if (y > 0 && map[y - 1][x] != '1' && map[y - 1][x]!= ' ')
		flag = 1;
	else if (map[y + 1] && map[y + 1][x] != '1' && map[y + 1][x] != ' ')
		flag = 1;
	if (flag)
		return (error_handler("map isn't surrounded by walls", NULL,
					NULL, scene_data));
}

void	set_player_angle(t_config *scene_data, char player_char, int y,
	int x)
{
	if (scene_data->player_start_angle != -1)
		return (error_handler("duplicat player character in the map",
			NULL, NULL, scene_data));
	if (player_char == 'N')
		scene_data->player_start_angle = N_ANGLE;
	else if (player_char == 'W')
		scene_data->player_start_angle = W_ANGLE;
	else if (player_char == 'E')
		scene_data->player_start_angle = E_ANGLE;
	else if (player_char == 'S')
		scene_data->player_start_angle = S_ANGLE;
	player_space_border_check(scene_data, y, x);
}

void map_parser(char **map, t_config *scene_data)
{
	int x;
	int y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		if ((y == 0 || !map[y + 1]) && top_bottom_check(map[y]))
			return (error_handler("map isn't surrounded by walls",
					NULL, NULL, scene_data));
		while (map[y][++x])
		{
			if ((x = 0 || x == (int)ft_strlen(map[y]) - 1 - (map[y][ft_strlen
				(map[y]) - 1] == '\n')) && !ft_strchr(" 1", map[y][x]))
				return (error_handler("map isn't surrounded by walls",
						NULL, NULL, scene_data));
			if (!(map[y][x]))
				return (error_handler("invalid character in the map\n", NULL,
					NULL, scene_data));
			if (ft_strchr("SNWE", map[y][x]))
				set_player_angle(scene_data, map[y][x], y, x);
			if (map[y][x] == ' ')
				player_space_border_check(scene_data, y, x);
		}
	}
}
