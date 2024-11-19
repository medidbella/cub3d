/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:05 by midbella          #+#    #+#             */
/*   Updated: 2024/11/18 16:56:14 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_access(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char *append_char(char *str, char c)
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

char *read_line(int fd)
{
    char	*res;
    char	c;

	res = NULL;
    while (read(fd, &c, 1) > 0)
    {
        res = append_char(res, c);
        if (c == '\n')
            break;
    }
    return res;
}
