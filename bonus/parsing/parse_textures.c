/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:08:52 by midbella          #+#    #+#             */
/*   Updated: 2024/12/04 15:00:36 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_door_texture(char **words, char *line, t_config *scene_data)
{
	if (ft_strncmp(words[0], "DOOR", 5))
		error_handler("unknown element\n", words, line, scene_data);
	scene_data->textures_paths[DOOR_IDX] = ft_strtrim(words[1], "\n");
	return ;
}

void	alignment_check(char **map, int x, int y, t_config *scene_data)
{
	if (!((map[y][x + 1] == '1' || map[y][x - 1] == '1')
		|| (map[y - 1][x] == '1' || map[y + 1][x] == '1')))
		error_handler("doors must be vertically or horizontally \
surrounded by walls ('1')", NULL, NULL, scene_data);
	return ;
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
	return (get_door_texture(words, line, scene_data));
}
