/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:36:59 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/28 22:48:33 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	get_strat(t_map *map, t_goal **goal, t_adv *adv)
{
	t_point coord1;
	t_point coord2;

	if (!*goal)
	{
		if (!get_advantage(map))
			return (0);
		coord1 = (t_point){map->width, 0};
		coord2 = (t_point){0, map->height};
		if ((map->my_pos.y < map->adv_pos.y && map->my_pos.x > map->adv_pos.x)
		|| (map->my_pos.y > map->adv_pos.y && map->my_pos.x < map->adv_pos.x))
		{
			coord1 = (t_point){0, 0};
			coord2 = (t_point){map->width, map->height};
		}
		if (get_norm(coord1.y, map->adv_pos.y, coord1.x, map->adv_pos.x)
				> get_norm(coord2.y, map->adv_pos.y, coord2.x, map->adv_pos.x))
			adv->other.coord = (t_point){coord1.x, coord1.y};
		else
			adv->other.coord = (t_point){coord2.x, coord2.y};
		*goal = &adv->other;
	}
	else if (finish_goal(goal, map))
		return (0);
	return (1);
}

static int	get_player_info(t_map *map)
{
	char	*line;

	line = NULL;
	map->order = 0;
	if (get_next_line(0, &line) == 1 && (!ft_strncmp(line, "$$$ exec p2 : ", 14)
				|| !ft_strncmp(line, "$$$ exec p1 : ", 14)))
	{
		map->order = line[10] - 48;
		map->my_sign = map->order == 1 ? 'O' : 'X';
		map->adv_sign = map->order == 1 ? 'X' : 'O';
	}
	free(line);
	return (map->order);
}

static int	play(t_map *map, t_piece *piece, t_goal **goal, t_adv *adv)
{
	if (!get_player_info(map))
		return (1);
	while (1)
	{
		if (!get_map(map))
			return (1);
		if ((map->loop++ == 1 || map->strat == 1)
				&& ((map->strat = get_strat(map, goal, adv)) == -1))
		{
			free_content(&map->content, map->height);
			free_content(&piece->content, piece->height);
		}
		if (!map->strat)
			choose_goal(map, goal, adv);
		if (!get_piece(piece))
		{
			free_content(&map->content, map->height);
			return (1);
		}
		if (!place_objectif(map, piece, *goal))
			return (0);
	}
	return (0);
}

int			main(void)
{
	t_map	map;
	t_piece	piece;
	t_goal	*goal;
	t_adv	adv;

	map.loop = 1;
	map.strat = 0;
	map.content = NULL;
	goal = NULL;
	adv.top = (t_goal){0, {0, 0}, 2147483647};
	adv.bottom = (t_goal){0, {0, 0}, -1};
	adv.right = (t_goal){0, {0, 0}, -1};
	adv.left = (t_goal){0, {0, 0}, 2147483647};
	return (play(&map, &piece, &goal, &adv));
}
