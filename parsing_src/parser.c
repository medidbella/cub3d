/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:52:51 by midbella          #+#    #+#             */
/*   Updated: 2024/11/07 18:37:08 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int format_check(char *str)
{
	int len;
	int i;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
			len++;
		else if (str[i] != ' ' && str[i] != '\n')
			return (1);
	}
	// printf("atoi = %d\nlen = %d\n", ft_atoi(str), len);
	i == 0;
	if (len > 3)
		return (1);
	if (ft_atoi(str) > 255)
		return (1);
	return (0);
}

void	color_parser(t_config *scene_data ,char *line, int type)
{
	char	*color;
	int		i;
	char	**rgb;

	i = 0;
	color = (char *)&scene_data->floor_color;
	if (type == CEILING)
		color = (char *)&scene_data->ceiling_color;
	if (*color != -1)
		error_handler("duplicate type element", NULL, line);
	rgb = ft_split(line + 1, ',');
	if (strings_len(rgb) != 3)
		error_handler("floor and ceiling color must be in format R,G,B \n",
			NULL, line);
	while (i < 3)
	{
		if (format_check(rgb[i]))
			error_handler("R,G,B colors must be in range [0,255]\n", rgb, NULL);
		color[i] = ft_atoi(rgb[i]);
		i++;
	}
	color[3] = 0;
}

void	get_textures(char **words, t_config *scene_data, char *line)
{
	int		i;
	char	*tab[5];

	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	tab[4] = NULL;
	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(words[0], tab[i], 3))
			break;
		i++;
	}
	if (i < 4)
	{
		if (scene_data->tab[i])
			error_handler("duplicate type element", words, line);
		return (scene_data->tab[i] = ft__strdup(words[1]), free(NULL));
	}
	if (!ft_strncmp(words[0], "F", 2) || !ft_strncmp(words[0], "C", 2))
		return (color_parser(scene_data, line, (words[0][0] == 'F')),
			strings_free(words));
	error_handler("unknown element\n", words, line);
}

int	line_parser(char *line, t_config *scene_data, int *map_flag)
{
	char	**words;

	if (line[0] == '\n')
		return (0);
	if (is_map_line(line) == 1)
		return (*map_flag = 1, 0);
	words = ft_split(line, ' ');
	if (!words)
		error_handler("insufficient memory\n", NULL, line);
	if (strings_len(words) != 2)
		error_handler("scene file syntax error\n each type element \
must be followed by one information\n", words, line);
	get_textures(words, scene_data, line);
	// strings_free(words);
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
		error_handler(strerror(errno), NULL, NULL);
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
	if (map_flag)
		printf("map found\n");
	free(line);
}

void	print_config(t_config *data)
{
	char	*tab[4];

	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	printf("C = %d\n", data->floor_color);
	printf("F = %d\n", data->ceiling_color);
	int i = 0;
	while (i <= 3 && data->tab[i])
	{
		printf("%s = %s\n", tab[i], data->tab[i]);
		i++;
	}
	i = 0;
	// while (i <= 3)
	// {
	// 	free(data->tab[i]);
	// 	i++;
	// }
}

int main()
{
	t_config data;
	int fd;
	file_parser(&data, "file");
	print_config(&data);
}