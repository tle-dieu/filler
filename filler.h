/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:42:08 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/19 01:41:32 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

typedef struct	s_map
{
	char	my_sign;
	char	adv_sign;
	int		order;
	char	**content;
	int		width;
	int		height;
	int		top;
	int		right;
	int		bottom;
	int		left;
	int		fd;		//A ENLEVER
}				t_map;

typedef	struct	s_enemy
{
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
}				t_enemy;

typedef struct  s_piece
{
	int         width;
	int         height;
	char        **content;
	int			stars;
	int			fd;
	int			first;
}               t_piece;

int     possible_to_place(t_map *map, t_piece *piece, int y, int x);
int     get_map(t_map *map);
int     get_piece(t_piece *piece);
int     place_top_left(t_map *map, t_piece *piece);
int     place_top_right(t_map *map, t_piece *piece);
int     place_down_left(t_map *map, t_piece *piece);
int     place_down_right(t_map *map, t_piece *piece);

#endif
