/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:22 by midbella          #+#    #+#             */
/*   Updated: 2024/11/06 14:52:24 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void data_init(t_config *data)
{
	data->map = NULL;
	data->player_start_angle = NULL;
	data->NO_texture_path = NULL;
	data->SO_texture_path = NULL;
	data->WE_texture_path = NULL;
	data->EA_texture_path = NULL;
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

void error_handl(char *err)
{
	write(2, "Error\n", 6);
	if (err)
		write(2, err, ft_strlen(err));
	exit(1);
}
