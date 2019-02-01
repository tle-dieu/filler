/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:44:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 17:12:15 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <stdlib.h>
#include <unistd.h>

int		print_piece(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	usleep(10000);
	if (!info_place(visu))
		return (0);
	if (!possible_to_place(visu, visu->y, visu->x))
		return (1);
	ft_printf("{#232323:bg}");
	while (j < visu->piece_h)
	{
		i = 0;
		while (i < visu->piece_w)
		{
			if (visu->piece[j][i] == '*')
			{
				ft_printf("\033[%d;%dH", 12 + visu->y + j, (visu->x + i) * 2 + visu->print_w);
				if (visu->actual_p == 'O')
					ft_printf("{#c3282f}"C_PLAY" ");
				else if (visu->actual_p == 'X')
					ft_printf("{#3e92cc}"C_PLAY" ");
			}
			++i;
		}
		++j;
	}
	ft_printf("\033[%d;0H{reset}", 12 + visu->map_h);
	return (1);
}

void	print_title(t_visu *visu)
{
	ft_printf("{#232323:bg}");
	ft_printf("%*c", visu->w.ws_row * visu->w.ws_col, ' ');
	visu->print_w = visu->w.ws_col / 2 - visu->map_w;
	ft_printf("\033[9;%dH{#232323:bg}", visu->print_w);
	ft_printf("{#c3282f}{bold}%-*s{#ffffff}{bold}", visu->map_w - 2, visu->p1);
	ft_printf("VS{#3e92cc}{bold}%*s\n", visu->map_w - 2, visu->p2);
	ft_printf("{reset}");
}

int		finish_game(t_visu *visu)
{
	char *line_x;

	line_x = NULL;
	free(visu->line);
	ft_printf("{#232323:bg}");
	if (visu->p1_score > visu->p2_score)
		ft_printf("\n{green}{bold}%s won 🏆\n", visu->p1);
	else if (visu->p1_score < visu->p2_score)
		ft_printf("\n{green}{bold}%s won 🏆\n", visu->p2);
	else
		ft_printf("\n{white}{bold}equality\n");
	ft_printf("{reset}");
	if (get_next_line(0, &line_x) != 1 || ft_strncmp(line_x, "== X fin:", 9))
	{
		free(line_x);
		return (1);
	}
	return (0);
}

void	print_score(t_visu *visu)
{
	int		width;
	float	p1;
	float	p2;
	int		i;
	float	map_size;

	width = visu->map_w * 2 - visu->score_len * 2;
	map_size = (float)visu->map_w * (float)visu->map_h / width;
	p1 = (float)visu->p1_score / map_size;
	p2 = (float)visu->p2_score / map_size;
	ft_printf("{#232323:bg}\033[%d;%dH", visu->map_h + 14, visu->print_w);
	ft_printf("{#c3282f}%-*d", visu->score_len, visu->p1_score);
	i = 0;
	while (++i <= (int)p1)
		ft_printf("●");
	i = 0;
	ft_printf("{#484848}");
	while (++i <= (width - (int)p2 - (int)p1))
		ft_printf("●");
	ft_printf("{#3e92cc}");
	i = 0;
	while (++i <= (int)p2)
		ft_printf("●");
	ft_printf("%*d\n{reset}", visu->score_len, visu->p2_score);
}

void	print_map(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	ft_printf("{#232323:bg}");
	while (j < visu->map_h)
	{
		i = 0;
		ft_printf("\033[%d;%dH", j + 12, visu->print_w);
		while (i < visu->map_w)
		{
			if (visu->map[j][i] == 'O')
				ft_printf("{#c3282f}"C_PLAY" ");
			else if (visu->map[j][i] == 'X')
				ft_printf("{#3e92cc}"C_PLAY" ");
			else
				ft_printf("{#484848}"C_PLAY" ");
			++i;
		}
		ft_printf("\n");
		++j;
	}
	ft_printf("{reset}");
}
