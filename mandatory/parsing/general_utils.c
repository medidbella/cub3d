/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:22 by midbella          #+#    #+#             */
/*   Updated: 2024/11/20 18:58:04 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_parsed_data(t_config *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(data->textures_paths[i]);
		i++;
	}
	if (data->map)
		strings_free(data->map);
}

void	data_init(t_config *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures_paths[i] = NULL;
		i++;
	}
	data->player_start_angle = -1;
	data->map = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
}

int	strings_len(char **words)
{
	int	len;

	len = 0;
	if (!words)
		return (0);
	while (words[len])
		len++;
	return (len);
}

void	strings_free(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		free(strings[i++]);
	free(strings);
}

void	error_handler(char *err, char **free_me, char *me_too, t_config *data)
{
	if (data)
		free_parsed_data(data);
	if (free_me)
		strings_free(free_me);
	free(me_too);
	write(2, "Error\n", 6);
	if (err)
		write(2, err, ft_strlen(err));
	exit (1);
}
