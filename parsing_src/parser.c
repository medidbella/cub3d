/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:51 by midbella          #+#    #+#             */
/*   Updated: 2024/11/06 16:01:37 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int data_filler(char **words, t_config *scene_data)
{
	int		i;
	char	**tab[4];

	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	i = 0;
	while (i < 3)
		if (words[0] == tab[i++])
			break;
	
}

int	line_parser(char *line, t_config *scene_data, int *map_flag)
{
	char	**words;

	if (line[0] == '\n')
		return (0);
	if (is_map_line(line))
		return (*map_flag = 1, 0);
	words = ft_split(line, ' ');
	if (!words)
		error_handl("insufficient memory\n");
	if (strings_len(words) != 2)
		error_handl("scene file syntax error\n each type element \
must be followed by one information\n");
	if (!is_element(words[0]))
		error_handl("unknown element\n");
	data_filler()
}

int file_parser(t_config *scene_data, char *scene_descrption_file)
{
	int		map_flag;
	int		fd;
	char	*line;

	map_flag = 0;
	data_init(scene_data);
	fd = open(scene_descrption_file, O_RDONLY);
	if (!fd)
		error_handle(strerror(errno));
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		line_parser(line, scene_data, &map_flag);
		if (map_flag)
			break;
		free(line);
	}
}
