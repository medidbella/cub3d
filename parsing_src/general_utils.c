/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:22 by midbella          #+#    #+#             */
/*   Updated: 2024/11/07 18:24:36 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	data_init(t_config *data)
{
	data->NO_texture_path = NULL;
	data->SO_texture_path = NULL;
	data->WE_texture_path = NULL;
	data->EA_texture_path = NULL;
	data->player_start_angle = 0;
	data->map = NULL;
	data->tab[0] = data->NO_texture_path;
	data->tab[1] = data->SO_texture_path;
	data->tab[2] = data->WE_texture_path;
	data->tab[3] = data->EA_texture_path;
	data->floor_color = -1;
	data->ceiling_color = -1;
}

int strings_len(char **words)
{
	int len;

	len = 0;
	if (!words)
		return (0);
	while (words[len])
		len++;
	return (len);
}

void	strings_free(char **strings)
{
	int i;

	i = 0;
	while(strings[i])
		free(strings[i++]);
	free(strings);
}

void error_handler(char *err, char **free_me, char *me_too)
{
	strings_free(free_me);
	free(me_too);
	write(2, "Error\n", 6);
	if (err)
		write(2, err, ft_strlen(err));
	exit(1);
}
 