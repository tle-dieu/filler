/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:57:59 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/02 13:40:58 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <stdlib.h>

int			get_score(t_visu *visu)
{
	int y;
	int x;

	y = 0;
	visu->p1_score = 0;
	visu->p2_score = 0;
	while (y < visu->map_h)
	{
		x = 0;
		while (x < visu->map_w)
		{
			if (visu->map[y][x] == 'x' || visu->map[y][x] == 'X')
				++visu->p2_score;
			else if (visu->map[y][x] == 'o' || visu->map[y][x] == 'O')
				++visu->p1_score;
			++x;
		}
		++y;
	}
	print_score(visu);
	return (1);
}

static int	get_map_info(t_visu *visu)
{
	char *tmp;

	free_content(&visu->map, visu->map_h);
	visu->map_w = 0;
	visu->map_h = 0;
	tmp = visu->line + 8;
	while (*tmp >= '0' && *tmp <= '9')
		visu->map_h = visu->map_h * 10 + *tmp++ - 48;
	if (*tmp && *tmp++ != ' ')
		visu->map_h = 0;
	while (*tmp >= '0' && *tmp <= '9')
		visu->map_w = visu->map_w * 10 + *tmp++ - 48;
	if (*tmp && *tmp != ':' && !*(tmp + 1))
		visu->map_w = 0;
	return (visu->map_h && visu->map_w);
}

int			get_map(t_visu *visu)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if ((get_map_info(visu)) != 1 || get_next_line(0, &line) != 1
	|| !(visu->map = (char **)malloc(sizeof(char *) * visu->map_h)))
	{
		free(line);
		return (1);
	}
	free(line);
	while (i < visu->map_h && get_next_line(0, &line) == 1)
	{
		if ((int)ft_strlen(line) - 4 != visu->map_w
		|| !(visu->map[i++] = ft_strdup(line + 4)))
		{
			free(line);
			free_content(&visu->map, i);
			return (-1);
		}
		free(line);
	}
	return (i == visu->map_h);
}

static int	get_piece_info(t_visu *visu)
{
	char *tmp;

	free_content(&visu->piece, visu->piece_h);
	visu->piece_h = 0;
	visu->piece_w = 0;
	tmp = visu->line + 6;
	while (*tmp >= '0' && *tmp <= '9')
		visu->piece_h = visu->piece_h * 10 + *tmp++ - 48;
	if (*tmp && *tmp++ != ' ')
		visu->piece_h = 0;
	while (*tmp >= '0' && *tmp <= '9')
		visu->piece_w = visu->piece_w * 10 + *tmp++ - 48;
	if (*tmp && *tmp != ':' && !*(tmp + 1))
		visu->piece_w = 0;
	return (visu->piece_w && visu->piece_h);
}

int			get_piece(t_visu *visu)
{
	int		j;
	char	*line;

	j = 0;
	line = NULL;
	if (!get_piece_info(visu)
			|| !(visu->piece = (char **)malloc(sizeof(char *) * visu->piece_h)))
	{
		free(line);
		return (0);
	}
	while (j < visu->piece_h && get_next_line(0, &line))
	{
		visu->piece[j++] = line;
		if ((int)ft_strlen(line) != visu->piece_w)
		{
			free_content(&visu->piece, j);
			return (0);
		}
	}
	return (1);
}
