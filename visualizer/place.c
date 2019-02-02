/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:13:12 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/02 13:38:13 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <unistd.h>

int		info_place(t_visu *visu)
{
	char	*line;
	char	*tmp;
	int		error;
	int		sign;

	line = visu->line;
	error = 1;
	visu->y = 0;
	visu->x = 0;
	sign = 1;
	visu->actual_p = line[6];
	tmp = line + 11;
	tmp = atoi_jr_v2(tmp, &visu->y);
	if (*tmp && *tmp++ != ',')
		error = 0;
	if (*tmp && *tmp++ != ' ')
		error = 0;
	tmp = atoi_jr_v2(tmp, &visu->x);
	if (*tmp && *tmp != ']' && !*(tmp + 1))
		error = 0;
	return (error);
}

int		possible_to_place(t_visu *visu, int y, int x)
{
	int j;
	int i;
	int connect;

	j = 0;
	connect = 0;
	usleep(10000);
	while (j < visu->piece_h)
	{
		i = 0;
		while (i < visu->piece_w)
		{
			if (visu->piece[j][i] == '*')
			{
				if ((x + i >= visu->map_w || y + j >= visu->map_h || y + j < 0
				|| x + i < 0) || (((visu->map[y + j][x + i] != visu->actual_p
				&& visu->map[y + j][x + i] != visu->actual_p + 32)
				|| ++connect > 1) && (visu->map[y + j][x + i] != '.')))
					return (0);
			}
			i++;
		}
		j++;
	}
	return (connect);
}
