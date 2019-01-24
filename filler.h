/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:42:08 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/24 21:16:35 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define MAP_CONTENT map->content[map->coord.y][map->coord.x]
# define PLAYER_NAME 17

# include "libft.h"
# include <stdlib.h>

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct	s_goal
{
	int			diff;
	t_point		coord;
	int			last;
}				t_goal;

typedef struct	s_norm
{
	t_point		coord;
	long long	dist;
}				t_norm;

typedef struct	s_map
{
	char		my_sign;
	char		adv_sign;
	int			order;
	char		**content;
	int			width;
	int			height;
	t_point		adv_pos;
	t_point		my_pos;
	t_point		coord;
	int			fd;//A ENLEVER
}				t_map;

typedef	struct	s_adv
{
	t_goal		top;
	t_goal		right;
	t_goal		bottom;
	t_goal		left;
}				t_adv;

typedef struct	s_piece
{
	int			width;
	int			height;
	char		**content;
	int			fd;
	int			first;
}				t_piece;

int				get_map_info(t_map *map);
int				get_map(t_map *map);
int				get_piece_info(t_piece *piece);
int				get_piece(t_piece *piece);
int				place_objectif(t_map *map, t_piece *piece, t_goal *goal);
void			choose_goal(t_map *map, t_goal **goal, t_adv *adv);
int				get_strat(t_map *map, t_goal **goal);

#endif
