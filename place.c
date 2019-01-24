/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:07:43 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/24 21:27:29 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		possible_to_place(t_map *map, t_piece *piece, int y, int x)
{
	int j;
	int i;
	int connect;

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

int		comp_dist(t_piece *piece, t_goal *goal, t_point coord, t_norm *norm)
{
	int			i;
	int			j;
	long long	dist;
	long long	tmp;

	j = piece->first;
	dist = norm->dist;
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			if (piece->content[j][i] == '*')
			{
				tmp = (goal->coord.y - coord.y - j) * (goal->coord.y - coord.y - j);
				tmp += (goal->coord.x - coord.x - i) * (goal->coord.x - coord.x - i);
				if (tmp < dist || dist == -1)
					dist = tmp;
			}
			++i;
		}
		++j;
	}
	if (dist < norm->dist || norm->dist == -1)
	{
		norm->dist = dist;
		return (1);
	}
	return (0);
}

int		place_objectif(t_map *map, t_piece *piece, t_goal *goal)
{
	t_norm norm;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	map->coord.y = -piece->height + 1;
	norm = (t_norm){{0, 0}, -1};
	while (map->coord.y < map->height)
	{
		map->coord.x = -piece->width + 1;
		while (map->coord.x < map->width)
		{
			if (possible_to_place(map, piece, map->coord.y, map->coord.x))
			{
				if (comp_dist(piece, goal, map->coord, &norm))
				{
					norm.coord.x = map->coord.x;
					norm.coord.y = map->coord.y;
				}
			}
			++map->coord.x;
		}
		++map->coord.y;
	}
	ft_printf("%d %d\n", norm.coord.y, norm.coord.x);
	return (norm.dist != -1);
}
