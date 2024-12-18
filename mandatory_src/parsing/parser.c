/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:51 by midbella          #+#    #+#             */
/*   Updated: 2024/12/18 19:08:44 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
int	format_check(char *str)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
			len++;
		else if (str[i] != ' ' && str[i] != '\n')
			return (1);
	}
	if (len > 3)
		return (1);
	if (ft_atoi(str) > 255)
		return (1);
	return (0);
}

void	color_parser(t_config *scene_data, char *line, int type)
{
	char	*color;
	int		i;
	char	**rgb;

	i = 0;
	color = (char *)&scene_data->floor_color;
	if (type == CEILING)
		color = (char *)&scene_data->ceiling_color;
	if (*color != -1)
		error_handler("duplicate type element", NULL, line, scene_data);
	rgb = ft_split(line + 1, ',');
	if (strings_len(rgb) != 3)
		error_handler("floor and ceiling color must be in format R,G,B \n",
			rgb, line, scene_data);
	while (i < 3)
	{
		if (format_check(rgb[i]))
			error_handler("R,G,B colors must be in range [0,255]\n",
				rgb, NULL, scene_data);
		color[i] = ft_atoi(rgb[i]);
		i++;
	}
	color[3] = 0;
	strings_free(rgb);
}

void	get_textures(char **words, t_config *scene_data, char *line)
{
	int		i;
	char	*tab[5];

	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	tab[4] = NULL;
	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(words[0], tab[i], 3))
			break ;
		i++;
	}
	if (i < 4)
	{
		if (scene_data->textures_paths[i])
			error_handler("duplicate type element", words, line, scene_data);
		return (scene_data->textures_paths[i] = ft_strtrim(words[1], "\n"),
			free(NULL));
	}
	if (!ft_strncmp(words[0], "F", 2) || !ft_strncmp(words[0], "C", 2))
		return (color_parser(scene_data, line, (words[0][0] == 'F')));
	error_handler("unknown element\n", words, line, scene_data);
}

void	line_parser(char *line, t_config *scene_data, int *map_flag)
{
	char	**words;

	if (line[0] == '\n')
		return ;
	if (is_map_line(line))
	{
		*map_flag = 1;
		return ;
	}
	words = ft_split(line, ' ');
	if (!words)
		error_handler("insufficient memory\n", NULL, line, scene_data);
	if (strings_len(words) != 2)
		error_handler("scene file syntax error\n each type element \
must be followed by one information\n", words, line, scene_data);
	get_textures(words, scene_data, line);
	strings_free(words);
}

void	file_parser(t_config *scene_data, char *scene_descrption_file)
{
	int		map_flag;
	int		fd;
	char	*line;

	map_flag = 0;
	data_init(scene_data);
	fd = open_cub_file(scene_descrption_file);
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		line_parser(line, scene_data, &map_flag);
		if (map_flag)
			break ;
		free(line);
	}
	if (!map_flag)
		error_handler("there no map in the file\n", NULL, line, scene_data);
	check_prev_members(scene_data, line);
	scene_data->map = map_alloc(line, fd, scene_data);
	map_parser(scene_data->map, scene_data);
	set_hight_width(scene_data);
}
