/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:58 by midbella          #+#    #+#             */
/*   Updated: 2024/11/18 17:36:53 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_prev_members(t_config *scene_data, char *line)
{
	int i;

	i = 0;
	while (i <= 3)
	{
		if (!scene_data->textures_paths[i])
			error_handler("incomplete elements\n", NULL, line, scene_data);
		if (!ft_access(scene_data->textures_paths[i]))
		{
			write(2, "Error\ncan't access \"", 20);
			ft_putstr_fd(scene_data->textures_paths[i], 2);
			write(2, "\"\n", 2);
			free_parsed_data(scene_data);
			free(line);
			exit(1);
		}
		i++;
	}
	if (scene_data->ceiling_color == -1 || scene_data->floor_color == -1)
			return (1);
	return (0);
}


int	is_map_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(" 10NSWE\n", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int top_bottom_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int open_cub_file(char *file)
{
	int		fd;
	char	*dot_occur;
	
	dot_occur = ft_strrchr(file, '.');
	if (!dot_occur || ft_strlen(file) == 4)
		error_handler("invalid file format\n", NULL, NULL, NULL);
	if (ft_strncmp(dot_occur, ".cub", 5))
		error_handler("invalid file format\n", NULL, NULL, NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handler("can't open the provided file\n", NULL, NULL, NULL);
	return (fd);
}