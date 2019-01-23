/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:09:03 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/21 18:43:08 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int     place_top_left(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	while (y < map->height)
	{
		x = -piece->width + 1;
		while (x < map->width)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			++x;
		}
		++y;
	}
	ft_printf("0 0\n");
	return (0);
}


int		comp_dist(t_piece *piece, t_point *goal, int x, int y, t_dist *coord)
{
	int i;
	int j;
	long long dist;
	long long tmp;

	j = piece->first;
	dist = coord->dist;
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			if (piece->content[j][i] == '*')
			{
				/* ft_dprintf(piece->fd, "coord: x: %d y: %d\n", x, y); */
				/* ft_dprintf(piece->fd, "coord: x + i: %d y + j: %d\n", x + i, y + j); */
				tmp = (goal->y - y - j) * (goal->y - y - j);
				/* ft_dprintf(piece->fd, "dist x: %d\n", (goal->x - x - i) * (goal->x - x - i)); */ 
				/* ft_dprintf(piece->fd, "dist y: %d\n", tmp); */
				tmp += (goal->x - x - i) * (goal->x - x - i);
				if (tmp < dist || dist == -1)
					dist = tmp;
			}
			++i;
		}
		++j;
	}
	/* ft_dprintf(piece->fd, "x: %d y: %d\n", x, y); */
	if (dist < coord->dist || coord->dist == -1)
	{
		coord->dist = dist;
		return (1);
	}
	return (0);
}

int     place_objectif(t_map *map, t_piece *piece, t_point *goal)
{
	t_dist coord;
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	coord = (t_dist){0,0,-1};
	while (y < map->height)
	{
		x = -piece->width + 1;
		while (x < map->width)
		{
			if (possible_to_place(map, piece, y, x))
			{
				if (comp_dist(piece, goal, x, y, &coord))
				{
					coord.x = x;
					coord.y = y;
				}
			}
			++x;
		}
		++y;
	}
	ft_printf("%d %d\n", coord.y, coord.x);
	return (coord.dist != -1);
}

int     place_top_right(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	while (y < map->height)
	{
		x = map->width;
		while (x > -piece->width)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_dprintf(map->fd, "coord: y = %d x = %d\n", y, x);
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			--x;
		}
		++y;
	}
	ft_printf("0 0\n");
	return (0);
}

int     place_down_left(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = map->height;
	while (y > -piece->height)
	{
		x = -piece->width + 1;
		while (x < map->width)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_dprintf(map->fd, "coord: y = %d x = %d\n", y, x);
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			++x;
		}
		--y;
	}
	ft_printf("0 0\n");
	return (0);
}

int     place_down_right(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = map->height;
	while (y > -piece->height)
	{
		x = map->width;
		while (x > -piece->width)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_dprintf(map->fd, "coord: y = %d x = %d\n", y, x);
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			--x;
		}
		--y;
	}
	ft_printf("0 0\n");
	return (0);
}
