/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:58 by midbella          #+#    #+#             */
/*   Updated: 2024/11/06 15:35:25 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int is_map_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' ||
		c == 'N' || c == 'S' || c == 'W' || c == 'E');
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

int is_element(char *str)
{
	return (!ft_strncmp(str, "NO", 3) || !ft_strncmp(str, "SO", 3)
		|| !ft_strncmp(str, "WE", 3) || !ft_strncmp(str, "EA", 3)
		|| !ft_strncmp(str, "F", 2), !ft_strncmp(str, "C", 2));
}