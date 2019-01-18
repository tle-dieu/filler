/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:42:08 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/18 14:18:21 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H

# define FILLER_H

typedef struct	s_map
{
	char	my_sign;
	char	adv_sign;
	int		order;
	char	**content;
	int		x_max;
	int		y_max;
	int		fd;		//A ENLEVER
}				t_map;

typedef struct  s_piece
{
	int         width;
	int         height;
	char        **content;
	int			stars;
	int			fd;
	int			first;
}               t_piece;

#endif
