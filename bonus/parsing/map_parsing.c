/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:44:23 by midbella          #+#    #+#             */
/*   Updated: 2024/11/27 19:42:13 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**map_alloc(char *line, int fd, t_config *scene_data)
{
	char	**res;
	char	*new_line;
	char	*tmp;

	new_line = read_line(fd);
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

void	player_space_border_check(t_config *scene_data, int y, int x, char c)
{
	int		flag;
	char	*set;
	char	**map;

	flag = 0;
	map = scene_data->map;
	set = " 1";
	if (c == 'p')
		set = "10VH";
	if (map[y][x + 1] && !ft_strchr(set, map[y][x + 1]))
		flag = 1;
	else if (x > 0 && !ft_strchr(set, map[y][x - 1]))
		flag = 1;
	else if (y > 0 && (int)ft_strlen(map[y - 1]) >= x
		&& !ft_strchr(set, map[y - 1][x]))
		flag = 1;
	else if (map[y + 1] && (int)ft_strlen(map[y + 1]) >= x
		&& !ft_strchr(set, map[y + 1][x]))
		flag = 1;
	if (flag)
		error_handler("map isn't surrounded by walls", NULL,
			NULL, scene_data);
}

void	set_player_angle(t_config *scene_data, char player_char, int y,
	int x)
{
	if (scene_data->player_start_angle != -1)
		error_handler("duplicat player character in the map",
			NULL, NULL, scene_data);
	if (player_char == 'N')
		scene_data->player_start_angle = N_ANGLE;
	else if (player_char == 'W')
		scene_data->player_start_angle = W_ANGLE;
	else if (player_char == 'E')
		scene_data->player_start_angle = E_ANGLE;
	else if (player_char == 'S')
		scene_data->player_start_angle = S_ANGLE;
	player_space_border_check(scene_data, y, x, 'p');
}

void	map_pars_helper(char **map, int y, int x, t_config *scene_data)
{
	if (!ft_strchr(" 01NSWEVH", map[y][x]))
		error_handler("use of invalid character in the map\n", NULL,
			NULL, scene_data);
	if (ft_strchr("SNWE", map[y][x]))
		set_player_angle(scene_data, map[y][x], y, x);
	if (ft_strchr("0VH", map[y][x]) && ((int)ft_strlen(map[y - 1]) <= x
		|| (int)ft_strlen(map[y + 1]) <= x))
		error_handler("map isn't surrounded by walls",
			NULL, NULL, scene_data);
	if (map[y][x] == 'H' || map[y][x] == 'V')
	{
		if (!scene_data->textures_paths[DOOR_IDX])
			error_handler
				("door present in tha map but it's texture isn't specified\n"
				, NULL, NULL, scene_data);
		alignement_check(map, x, y, scene_data);
		scene_data->door_flag = 1;
	}
	if (map[y][x] == ' ')
		player_space_border_check(scene_data, y, x, ' ');
}

void	map_parser(char **map, t_config *scene_data)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		if ((y == 0 || !map[y + 1]) && top_bottom_check(map[y]))
			error_handler("map isn't surrounded by walls",
				NULL, NULL, scene_data);
		while (map[y][++x])
		{
			if ((x == 0 || x == (int)ft_strlen(map[y]) - 1)
				&& !ft_strchr(" 1", map[y][x]))
				error_handler("map isn't surrounded by walls", NULL, NULL,
					scene_data);
			map_pars_helper(map, y, x, scene_data);
			if (x > scene_data->map_width)
				scene_data->map_width = x + 1;
		}
	}
	if (scene_data->player_start_angle == -1)
		error_handler("palayer not found in the map\n", NULL, NULL, scene_data);
}
