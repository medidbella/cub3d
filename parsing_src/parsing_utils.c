/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:58 by midbella          #+#    #+#             */
/*   Updated: 2024/11/06 21:52:07 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
