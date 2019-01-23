/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:17:31 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/21 18:13:40 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h> // a retirer
#include <stdlib.h>
#define PLAYER_NAME 17

/*
 * -place avec map plus petite
 * -
 * 
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

void	get_enemy_info(t_map *map, t_enemy *enemy)
{
	int x;
	int y;
	int change;

	y = 0;
	change = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->content[y][x] == map->adv_sign)
			{
				if (y - 1 <= (change & 0xF000 ? enemy->top.y : enemy->top.last - 1))
				{
					enemy->top.y = y - 1;
					enemy->top.x = x;
					change = (change & 0x0FFF) | 0x1000;
				}
				if (y + 1 >= (change & 0x0F00 ? enemy->bottom.y : enemy->bottom.last + 1))
				{
					enemy->bottom.y = y + 1;
					enemy->bottom.x = x;
					change = (change & 0xF0FF) | 0x0100;
				}
				if (x + 1 >= (change & 0x00F0 ? enemy->right.x : enemy->right.last + 1))
				{
					enemy->right.y = y;
					enemy->right.x = x + 1;
					change = (change & 0xFF0F) | 0x0010;
				}
				if (x - 1 <= (change & 0x000F ? enemy->left.x : enemy->left.last - 1))
				{
					enemy->left.y = y;
					enemy->left.x = x - 1;
					change = (change & 0xFFF0) | 0x0001;
				}
			}
			++x;
		}
		++y;
	}
	enemy->top.diff = enemy->top.last - enemy->top.y;
	enemy->top.last = enemy->top.y;
	enemy->right.diff = enemy->right.x - enemy->right.last;
	enemy->right.last = enemy->right.x;
	enemy->bottom.diff = enemy->bottom.y - enemy->bottom.last;
	enemy->bottom.last = enemy->bottom.y;
	enemy->left.diff = enemy->left.last - enemy->left.x;
	enemy->left.last = enemy->left.x;
}

void	choose_goal(t_map *map, t_piece *piece, t_enemy *enemy, t_point **goal)
{
	(void)map;
	(void)piece;
	ft_dprintf(map->fd, "right: %d\n", enemy->right.diff);
	ft_dprintf(map->fd, "left: %d\n", enemy->left.diff);
	ft_dprintf(map->fd, "top: %d\n", enemy->top.diff);
	ft_dprintf(map->fd, "bottom: %d\n", enemy->bottom.diff);
	if (enemy->right.diff)
		*goal = &enemy->right;
	if (enemy->top.diff > (*goal)->diff)
		*goal = &enemy->top;
	if (enemy->left.diff > (*goal)->diff)
		*goal = &enemy->left;
	if (enemy->bottom.diff > (*goal)->diff)
		*goal = &enemy->bottom;
	ft_dprintf(map->fd, "obj: x: %d y: %d\n", (*goal)->x, (*goal)->y);
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
				if (y + j < 0 || y + j >= map->height || x + i < 0 || x + i >= map->width)
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
	t_enemy	enemy;
	t_point	*goal;
	int		j;
	int		loop;

	loop = 1;
	map.content = NULL;
	map.fd = open("./result/read.txt",  O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	piece.fd = map.fd;
	ft_dprintf(map.fd, "{green}----------INFO MAP----------{reset}\n\n");
	if (!get_player_info(&map))
		return (1);
	enemy.top = (t_point){0,0,0,2147483647};
	enemy.bottom = (t_point){0,0,0,-1};
	enemy.right = (t_point){0,0,0,-1};
	enemy.left = (t_point){0,0,0,2147483647};
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
		while (j < map.height)
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
		get_enemy_info(&map, &enemy);
		choose_goal(&map, &piece, &enemy, &goal);
		if (!place_objectif(&map, &piece, goal))
		{
			ft_dprintf(map.fd, "error place piece\n");
			return (1);
		}
		ft_dprintf(map.fd, "piece placee\n\n");
	}
	return (0);
}
