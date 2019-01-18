/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:17:31 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/18 20:33:24 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h> // a retirer
#include <stdlib.h>
#define PLAYER_NAME 17

/*
 * Faire map analyse pour trouver cotes fermes et autres
 * faire fonction direction enemy
 * faire fonction position players
 */

int		get_player_info(t_map *map)
{
	char	*line;
	int		len;

	line = NULL;
	map->order = 0;
	if (get_next_line(0, &line) == 1 && (len = ft_strlen(line)) >= PLAYER_NAME + 16
			&& (!ft_strncmp(line, "$$$ exec p2 : [", 15) || !ft_strncmp(line, "$$$ exec p1 : [", 15))
			&& !ft_strcmp(line + len - PLAYER_NAME, "/tle-dieu.filler]"))
	{
		map->order = line[10] - 48;
		map->my_sign = map->order == 1 ? 'O' : 'X';
		map->adv_sign = map->order == 1 ? 'X' : 'O';
		ft_dprintf(map->fd, "player info: %s\n", line);
	}
	free(line);
	ft_dprintf(map->fd, "fin get_player_info\n");
	return (map->order);
}

int		possible_to_place(t_map *map, t_piece *piece, int y, int x)
{
	int	j;
	int	i;
	int	connect;

	j = piece->first;
	connect = 0;
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			if (piece->content[j][i] == '*')
			{
				if (y + j < 0 || y + j >= map->y_max || x + i < 0 || x + i >= map->x_max)
					return (0);
				if ((map->content[y + j][x + i] != map->my_sign || ++connect > 1) && (map->content[y + j][x + i] != '.'))
					return (0);
			}	
			i++;
		}
		j++;
	}
	return (connect);
}

int		main(void)
{
	t_map	map;
	t_piece piece;
	int		j;
	int		loop;

	loop = 1;
	map.content = NULL;
	map.fd = open("./result/read.txt",  O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	piece.fd = map.fd;
	ft_dprintf(map.fd, "{green}----------INFO MAP----------{reset}\n\n");
	if (!get_player_info(&map))
		return (1);
	ft_dprintf(map.fd, "order: %d\nmy sign: %c\nadv sign: %c\n\n", map.order, map.my_sign, map.adv_sign);
	while (1)
	{
		ft_dprintf(map.fd, "{cyan}----------TOUR %d----------{reset}\n", loop++);
		if (!get_map(&map))
		{
			ft_dprintf(map.fd, "error map\n");
			return (1);
		}
		j = 0;
		ft_dprintf(map.fd, "{#de6864}-----MAP-----{reset}\n");
		ft_dprintf(map.fd, "    01234567890123456789012345678901234567890123456789\n");
		while (j < map.y_max)
		{
			ft_dprintf(map.fd, "%.3d ", j);
			ft_dprintf(map.fd, "%s\n", map.content[j++]);
		}
		if (!get_piece(&piece))
		{
			ft_dprintf(map.fd, "error piece\n");
			return (1);
		}
		j = 0;
		ft_dprintf(map.fd, "{#fb3268}-----PIECE-----{reset}\n");
		while (j < piece.height)
			ft_dprintf(map.fd, "%s\n", piece.content[j++]);
		if (!place_top_left(&map, &piece))
		{
			ft_dprintf(map.fd, "error place piece\n");
			return (1);
		}
		ft_dprintf(map.fd, "piece placee\n\n");
	}
	return (0);
}
