/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:36:59 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/24 21:26:08 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h> // a retirer

void	print_map(t_map *map)
{
	int j;

	j = 0;
	ft_dprintf(map->fd, "----------PRINT MAP----------\n");
	ft_dprintf(map->fd, "01234567890123456789012345678901234567890123456789\n");
	while (j < map->height)
	{
		ft_dprintf(map->fd, "%.3d%s\n", j, map->content[j]);
		++j;
	}
}

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

int		main(void)
{
	t_map	map;
	t_piece	piece;
	t_goal	*goal;
	int		loop;
	int		strat;
	t_adv	adv;

	loop = 1;
	strat = 0;
	map.content = NULL;
	goal = NULL;
	adv.top = (t_goal){0, {0, 0}, 2147483647};
	adv.bottom = (t_goal){0, {0, 0}, -1};
	adv.right = (t_goal){0, {0, 0}, -1};
	adv.left = (t_goal){0, {0, 0}, 2147483647};
	map.fd = open("./result/read.txt", O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	piece.fd = map.fd;
	if (!get_player_info(&map))
		return (1);
	ft_dprintf(map.fd, "order: %d\nmy sign: %c\nadv sign: %c\n\n", map.order, map.my_sign, map.adv_sign);
	while (1)
	{
		if (!get_map(&map))
			return (1);
		print_map(&map);
		if (loop++ == 1 || strat == 1)
			strat = get_strat(&map, &goal);
		if (!strat)
			choose_goal(&map, &goal, &adv);
		if (!get_piece(&piece))
			return (1);
		if (!place_objectif(&map, &piece, goal))
			return (1);
	}
	return (0);
}
