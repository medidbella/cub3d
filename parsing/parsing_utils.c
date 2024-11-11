/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:58 by midbella          #+#    #+#             */
/*   Updated: 2024/11/09 17:54:03 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_prev_members(t_config *scene_data)
{
	int i;

	i = 0;
	while (i <= 3)
	{
		if (!scene_data->tab[i])
			return (write(1, "here1\n", 6), 1);
		i++;
	}
	if (scene_data->ceiling_color == -1 || scene_data->floor_color == -1)
			return (write(1, "here2\n", 6), 1);
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