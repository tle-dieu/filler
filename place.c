/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:07:43 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 14:35:29 by tle-dieu         ###   ########.fr       */
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
				if ((x + i >= map->width || y + j >= map->height
				|| y + j < 0 || x + i < 0)
				|| ((map->content[y + j][x + i] != map->my_sign
				|| ++connect > 1) && (map->content[y + j][x + i] != '.')))
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
			if ((piece->content[j][i] == '*') && ((tmp = get_norm(goal->Y,
			Y + j, goal->X, X + i)) < dist || dist == -1))
				dist = tmp;
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

	map->Y = -piece->height + 1;
	norm = (t_norm){{0, 0}, -1};
	while (map->Y < map->height)
	{
		map->X = -piece->width + 1;
		while (map->X < map->width)
		{
			if (possible_to_place(map, piece, map->Y, map->X))
			{
				if (comp_dist(piece, goal, map->coord, &norm))
					norm.coord = (t_point){map->X, map->Y};
			}
			++map->X;
		}
		++map->Y;
	}
	free_content(&map->content, map->height);
	free_content(&piece->content, piece->height);
	ft_printf("%d %d\n", norm.Y, norm.X);
	return (norm.dist != -1);
}
