/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:49:16 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/29 22:53:30 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

typedef struct	s_visu
{
	char		*p1;
	char		*p2;
	char		**map;
	int			height_map;
	int			width_map;
	int			p1_score;
	int			p2_score;
	char		*line;
}				t_visu;

#endif
