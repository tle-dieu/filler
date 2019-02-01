/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:51:09 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 14:33:21 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_map_info(t_map *map)
{
	char	*line;
	char	*tmp;

	map->width = 0;
	map->height = 0;
	line = NULL;
	if (get_next_line(0, &line) == 1 && !ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9')
			map->height = map->height * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			map->height = 0;
		while (*tmp >= '0' && *tmp <= '9')
			map->width = map->width * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			map->width = 0;
	}
	free(line);
	return (map->width && map->height);
}

int		get_map(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	map->content = NULL;
	if (!get_map_info(map) || get_next_line(0, &line) != 1
			|| !(map->content = (char **)malloc(sizeof(char *) * map->height)))
	{
		free(line);
		return (0);
	}
	free(line);
	while (i < map->height && get_next_line(0, &line) == 1)
	{
		if ((int)ft_strlen(line) - 4 != map->width
				|| !(map->content[i++] = ft_strdup(line + 4)))
		{
			free(line);
			free_content(&map->content, i);
			return (0);
		}
		free(line);
	}
	return (i == map->height);
}
