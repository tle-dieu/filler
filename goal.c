/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:55:50 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/03 14:42:36 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_max(int *change, t_adv *adv, t_map *map)
{
	if (map->Y - 1 <= (*change & 0xF000 ? adv->top.Y : adv->top.last - 1))
	{
		adv->top.Y = map->Y - 1;
		adv->top.X = map->X;
		*change = (*change & 0x0FFF) | 0x1000;
	}
	if (map->Y + 1 >= (*change & 0x0F00 ? adv->bottom.Y : adv->bottom.last + 1))
	{
		adv->bottom.Y = map->Y + 1;
		adv->bottom.X = map->X;
		*change = (*change & 0xF0FF) | 0x0100;
	}
	if (map->X + 1 >= (*change & 0x00F0 ? adv->right.X : adv->right.last + 1))
	{
		adv->right.Y = map->Y;
		adv->right.X = map->X + 1;
		*change = (*change & 0xFF0F) | 0x0010;
	}
	if (map->X - 1 <= (*change & 0x000F ? adv->left.X : adv->left.last - 1))
	{
		adv->left.Y = map->Y;
		adv->left.X = map->X - 1;
		*change = (*change & 0xFFF0) | 0x0001;
	}
}

void	get_adv_info(t_map *map, t_adv *adv)
{
	int change;

	change = 0;
	map->Y = 0;
	while (map->Y < map->height)
	{
		map->X = 0;
		while (map->X < map->width)
		{
			if (MAP_CONTENT == map->adv_sign)
				get_max(&change, adv, map);
			++map->X;
		}
		++map->Y;
	}
	adv->top.diff = adv->top.last - adv->top.Y;
	adv->top.last = adv->top.Y;
	adv->right.diff = adv->right.X - adv->right.last;
	adv->right.last = adv->right.X;
	adv->bottom.diff = adv->bottom.Y - adv->bottom.last;
	adv->bottom.last = adv->bottom.Y;
	adv->left.diff = adv->left.last - adv->left.X;
	adv->left.last = adv->left.X;
}

void	choose_goal(t_map *map, t_goal **goal, t_adv *adv)
{
	get_adv_info(map, adv);
	if (adv->right.diff)
		*goal = &adv->right;
	if (adv->top.diff > (*goal)->diff)
		*goal = &adv->top;
	if (adv->left.diff > (*goal)->diff)
		*goal = &adv->left;
	if (adv->bottom.diff > (*goal)->diff)
		*goal = &adv->bottom;
}

int		get_advantage(t_map *map)
{
	int adv;
	int my;

	my = 0;
	adv = 0;
	map->Y = -1;
	while (++map->Y < map->height)
	{
		map->X = 0;
		while (map->X < map->width)
		{
			if (MAP_CONTENT == map->my_sign)
			{
				my = get_norm(map->height / 2, map->Y, map->width / 2, map->X);
				map->my_pos = (t_point){map->X, map->Y};
			}
			else if (MAP_CONTENT == map->adv_sign)
			{
				adv = get_norm(map->height / 2, map->Y, map->width / 2, map->X);
				map->adv_pos = (t_point){map->X, map->Y};
			}
			++map->X;
		}
	}
	return (my > adv + adv / 2);
}

int		finish_goal(t_goal **goal, t_map *map)
{
	int y_max;
	int x_max;
	int x_tmp;

	y_max = !(*goal)->Y ? (*goal)->Y + 3 : (*goal)->Y;
	x_max = !(*goal)->X ? (*goal)->X + 3 : (*goal)->X;
	map->Y = !(*goal)->Y ? 0 : (*goal)->Y - 3;
	x_tmp = !(*goal)->X ? 0 : (*goal)->X - 3;
	while (map->Y < y_max)
	{
		map->X = x_tmp;
		while (map->X < x_max)
		{
			if (MAP_CONTENT == map->my_sign)
				return (1);
			++map->X;
		}
		++map->Y;
	}
	return (0);
}
