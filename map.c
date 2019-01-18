/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:06:56 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/18 19:12:57 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>

int     get_map_info(t_map *map)
{
	char    *line;
	char    *tmp;

	map->x_max = 0;
	map->y_max = 0;
	line = NULL;
	if (get_next_line(0, &line) == 1 && !ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9' )
			map->y_max = map->y_max * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			map->y_max = 0;
		while (*tmp >= '0' && *tmp <= '9' )
			map->x_max = map->x_max * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			map->x_max = 0;
	}
	free(line);
	ft_dprintf(map->fd, "fin get_map_info\n");
	return (map->x_max && map->y_max);
}

int     get_map(t_map *map)
{
	char    *line;
	int     i;

	i = 0;
	line = NULL;
	map->content = NULL;
	if (!get_map_info(map) || get_next_line(0, &line) != 1
			|| !(map->content = (char **)malloc(sizeof(char *) * map->y_max)))
	{
		free(line);
		return (0);
	}
	while (i < map->y_max && get_next_line(0, &line) == 1)
		map->content[i++] = line + 4; // free content en cas d'erreur / pareil pour get_piece
	i = 0;
	ft_dprintf(map->fd, "fin get_map\n");
	return (1);
}
