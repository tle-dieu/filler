/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:06:56 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/19 01:38:04 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>

int     get_map_info(t_map *map)
{
	char    *line;
	char    *tmp;

	map->width = 0;
	map->height = 0;
	line = NULL;
	if (get_next_line(0, &line) == 1 && !ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9' )
			map->height = map->height * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			map->height = 0;
		while (*tmp >= '0' && *tmp <= '9' )
			map->width = map->width * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			map->width = 0;
	}
	free(line);
	ft_dprintf(map->fd, "fin get_map_info\n");
	return (map->width && map->height);
}

int     get_map(t_map *map)
{
	char    *line;
	int     i;

	i = 0;
	line = NULL;
	map->content = NULL;
	if (!get_map_info(map) || get_next_line(0, &line) != 1
			|| !(map->content = (char **)malloc(sizeof(char *) * map->height)))
	{
		free(line);
		return (0);
	}
	while (i < map->height && get_next_line(0, &line) == 1)
		map->content[i++] = line + 4; // free content en cas d'erreur / pareil pour get_piece
	i = 0;
	ft_dprintf(map->fd, "fin get_map\n");
	return (1);
}
