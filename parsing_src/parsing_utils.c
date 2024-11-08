/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:58 by midbella          #+#    #+#             */
/*   Updated: 2024/11/08 21:56:03 by midbella         ###   ########.fr       */
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
	if (scene_data->ceiling_color == -1 || scene_data->floor_color == -1
		|| scene_data->player_start_angle == -1)
			return (write(1, "here2\n", 6), 1);
	return (0);
}

int is_map_char(char c)
{
	return (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W'
			|| c == 'E' || c == '\n');
}

int	is_map_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_map_char(str[i]))
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