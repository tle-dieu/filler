/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:49:16 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/31 16:57:45 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H
# define C_PLAY "◉"
//◉ ◼ ◯ ●▢ 
#include "libft.h"

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
int             get_map_infos(t_visu *visu);
int             get_map(t_visu *visu);
void			print_map(t_visu *visu);
void			free_content(char ***content, int height_map);

#endif
