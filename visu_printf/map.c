/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:26:37 by matleroy          #+#    #+#             */
/*   Updated: 2019/01/31 16:30:33 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "unistd.h"
#include "stdlib.h"


int     get_map_info(t_visu *visu)
{
	char    *tmp;

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

int        get_map(t_visu *visu)
{
	char    *line;
	int             i;
	int             ret;

	i = 0;
	line = NULL;
	visu->map = NULL;
	if ((ret = get_map_info(visu)) != 1)
		return (ret);
	if (get_next_line(0, &line) != 1
			|| !(visu->map = (char **)malloc(sizeof(char *) * visu->map_h)))
	{
		free(line);
		return (-1);
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

void    print_map(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	while (j < visu->map_h)
	{
		i = 0;
		ft_printf("   ");
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
}
