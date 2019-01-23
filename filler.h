/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:42:08 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/21 14:45:43 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define MY_SIGN(x) x == 1 ? 'O' : 'X'
# define AVD_SIGN(x) x == 2 ? 'O' : 'X'

// pour potentillement retirer vars `sign`

# include "libft.h"

typedef	struct	s_point
{
	int			x;
	int			y;
	int			diff;
	int			last;
}				t_point;

typedef struct	s_dist
{
	int			x;
	int			y;
	long long	dist;
}				t_dist;
typedef struct	s_map
{
	char		my_sign;
	char		adv_sign;
	int			order;
	char		**content;
	int			width;
	int			height;
	int			fd;//A ENLEVER
}				t_map;

typedef	struct	s_enemy
{
	t_point		top;
	t_point		right;
	t_point		bottom;
	t_point		left;
}				t_enemy;

typedef struct	s_piece
{
	int			width;
	int			height;
	char		**content;
	int			fd;
	int			first;
}				t_piece;

int				possible_to_place(t_map *map, t_piece *piece, int y, int x);
int				place_objectif(t_map *map, t_piece *piece, t_point *goal);
int				get_map(t_map *map);
int				get_piece(t_piece *piece);
int				place_top_left(t_map *map, t_piece *piece);
int				place_top_right(t_map *map, t_piece *piece);
int				place_down_left(t_map *map, t_piece *piece);
int				place_down_right(t_map *map, t_piece *piece);

#endif
