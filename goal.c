/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:55:50 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/24 21:40:39 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_adv_info(t_map *map, t_adv *adv)
{
	int change;

	change = 0;
	map->coord.y = 0;
	while (map->coord.y < map->height)
	{
		map->coord.x = 0;
		while (map->coord.x < map->width)
		{
			if (MAP_CONTENT == map->adv_sign)
			{
				if (map->coord.y - 1 <= (change & 0xF000 ? adv->top.coord.y : adv->top.last - 1))
				{
					adv->top.coord.y = map->coord.y - 1;
					adv->top.coord.x = map->coord.x;
					change = (change & 0x0FFF) | 0x1000;
				}
				if (map->coord.y + 1 >= (change & 0x0F00 ? adv->bottom.coord.y : adv->bottom.last + 1))
				{
					adv->bottom.coord.y = map->coord.y + 1;
					adv->bottom.coord.x = map->coord.x;
					change = (change & 0xF0FF) | 0x0100;
				}
				if (map->coord.x + 1 >= (change & 0x00F0 ? adv->right.coord.x : adv->right.last + 1))
				{
					adv->right.coord.y = map->coord.y;
					adv->right.coord.x = map->coord.x + 1;
					change = (change & 0xFF0F) | 0x0010;
				}
				if (map->coord.x - 1 <= (change & 0x000F ? adv->left.coord.x : adv->left.last - 1))
				{
					adv->left.coord.y = map->coord.y;
					adv->left.coord.x = map->coord.x - 1;
					change = (change & 0xFFF0) | 0x0001;
				}
			}
			++map->coord.x;
		}
		++map->coord.y;
	}
	adv->top.diff = adv->top.last - adv->top.coord.y;
	adv->top.last = adv->top.coord.y;
	adv->right.diff = adv->right.coord.x - adv->right.last;
	adv->right.last = adv->right.coord.x;
	adv->bottom.diff = adv->bottom.coord.y - adv->bottom.last;
	adv->bottom.last = adv->bottom.coord.y;
	adv->left.diff = adv->left.last - adv->left.coord.x;
	adv->left.last = adv->left.coord.x;
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
	ft_dprintf(map->fd, "obj: x: %d y: %d\n", (*goal)->coord.x, (*goal)->coord.y);
}

int		get_advantage(t_map *map)
{
	int adv_dist;
	int my_dist;

	my_dist = 0;
	adv_dist = 0;
	map->coord.y = 0;
	while (map->coord.y < map->height)
	{
		map->coord.x = 0;
		while (map->coord.x < map->width)
		{
			if (MAP_CONTENT == map->my_sign)
			{
				my_dist = (map->width / 2 - map->coord.x) * (map->width / 2 - map->coord.x) + (map->height / 2 - map->coord.y) * (map->height / 2 - map->coord.y);
				map->my_pos = (t_point){map->coord.x, map->coord.y};
			}
			else if (MAP_CONTENT == map->adv_sign)
			{
				adv_dist = (map->width / 2 - map->coord.x) * (map->width / 2 - map->coord.x) + (map->height / 2 - map->coord.y) * (map->height / 2 - map->coord.y);
				map->adv_pos = (t_point){map->coord.x, map->coord.y};
			}
			++map->coord.x;
		}
		++map->coord.y;
	}
	ft_dprintf(map->fd, "my_dist: %d adv_dist: %d\n", my_dist, adv_dist);
	return (my_dist > adv_dist + adv_dist / 2);
}

int		get_norm(t_point coord1, t_point coord2)
{
	int norm;

	norm = (coord1.x - coord2.x) * (coord1.x - coord2.x)
		+ (coord1.y - coord1.y) * (coord1.y - coord2.y);
	return (norm);
}

int		finish_goal(t_goal **goal, t_map *map)
{
	int y_max;
	int x_max;
	int x_tmp;

	y_max = !(*goal)->coord.y ? (*goal)->coord.y + 5 : (*goal)->coord.y;
	x_max = !(*goal)->coord.x ? (*goal)->coord.x + 5 : (*goal)->coord.x;
	map->coord.y = !(*goal)->coord.y ? 0 : (*goal)->coord.y - 5;
	x_tmp = !(*goal)->coord.x ? 0 : (*goal)->coord.x - 5;
	while (map->coord.y < y_max)
	{
		map->coord.x = x_tmp;
		while (map->coord.x < x_max)
		{
			if (MAP_CONTENT == map->my_sign)
				return (1);
			++map->coord.x;
		}
		++map->coord.y;
	}
	return (0);
}

int		get_strat(t_map *map, t_goal **goal)
{
	t_goal	*tmp;
	t_point	coord1;
	t_point	coord2;

	if (!*goal)
	{
		if (!get_advantage(map))
			return (0);
		if (!(tmp = (t_goal *)malloc(sizeof(t_goal))))
			return (0);
		ft_dprintf(map->fd, "disadvantage\n");
		if ((map->my_pos.y < map->adv_pos.y && map->my_pos.x > map->adv_pos.x)
				|| (map->my_pos.y > map->adv_pos.y && map->my_pos.x < map->adv_pos.x))
		{
			coord1 = (t_point){0, 0};
			coord2 = (t_point){map->width, map->height};
		}
		else
		{
			coord1 = (t_point){map->width, 0};
			coord2 = (t_point){0, map->height};
		}
		if (get_norm(coord1, map->adv_pos) > get_norm(coord2, map->adv_pos))
			tmp->coord = (t_point){coord1.x, coord1.y};
		else
			tmp->coord = (t_point){coord2.x, coord2.y};
		*goal = tmp;
	}
	else if (finish_goal(goal, map))
	{
		free(*goal);
		return (0);
	}
	return (1);
}
