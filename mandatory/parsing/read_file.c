/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:05 by midbella          #+#    #+#             */
/*   Updated: 2024/11/24 19:00:38 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_access(char *file, t_config *scene_data, char *line, int i)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\ncan't access \"", 20);
		ft_putstr_fd(scene_data->textures_paths[i], 2);
		write(2, "\"\n", 2);
		free_parsed_data(scene_data);
		free(line);
		exit(1);
	}
	close(fd);
	return ;
}

char	*append_char(char *str, char c)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		error_handler("insufficient memory\n", NULL, str, NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[len] = c;
	res[len + 1] = 0;
	free(str);
	return (res);
}

char	*read_line(int fd)
{
	char	*res;
	char	c;

	res = NULL;
	while (read(fd, &c, 1) > 0)
	{
		res = append_char(res, c);
		if (c == '\n')
			break ;
	}
	return (res);
}
