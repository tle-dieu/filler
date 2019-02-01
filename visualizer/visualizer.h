/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:49:16 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 18:26:50 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# define C_PLAY "◉"
# include "libft.h"
# include <sys/ioctl.h>

typedef struct		s_visu
{
	char			*p1;
	char			*p2;
	char			**map;
	int				map_h;
	int				map_w;
	int				p1_score;
	int				p2_score;
	char			*line;
	char			**piece;
	int				piece_w;
	int				piece_h;
	int				x;
	int				y;
	char			actual_p;
	int				print_w;
	struct winsize	w;
	int				score_len;
}					t_visu;

int					get_score(t_visu *visu);
int					get_piece(t_visu *visu);
int					info_place(t_visu *visu);
int					possible_to_place(t_visu *visu, int y, int x);
int					get_map(t_visu *visu);
void				free_content(char ***content, int height_map);
void				print_map(t_visu *visu);
int					int_len(int nb);
int					print_piece(t_visu *visu);
int					finish_game(t_visu *visu);
void				print_score(t_visu *visu);
void				print_background(t_visu *visu);
void				print_init(t_visu *visu);

#endif
