/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:49:16 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/30 03:19:19 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# define C_PLAY "◼"
//◉ ◼ ◯ ●▢ 

typedef struct	s_visu
{
	char		*p1;
	char		*p2;
	char		**map;
	int			map_h;
	int			map_w;
	int			p1_score;
	int			p2_score;
	char		*line;
	char		**piece;
	int			piece_w;
	int			piece_h;
	int			x;
	int			y;
	char		actual_p;
	int			fd;
}				t_visu;

#endif
