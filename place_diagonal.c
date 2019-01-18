/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:09:03 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/18 19:38:00 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int     place_top_left(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	while (y < map->y_max)
	{
		x = -piece->width + 1;
		while (x < map->x_max)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_dprintf(map->fd, "coord: y = %d x = %d\n", y, x);
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

int     place_top_rigth(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	while (y < map->y_max)
	{
		x = map->x_max;
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
	y = map->y_max;
	while (y > -piece->height)
	{
		x = -piece->width + 1;
		while (x < map->x_max)
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

int     place_down_rigth(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = map->y_max;
	while (y > -piece->height)
	{
		x = map->x_max;
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

