/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:58:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 18:27:28 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visualizer.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	get_player_name(t_visu *visu)
{
	char	*str;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (++i < 6 && get_next_line(0, &line) == 1)
		free(line);
	while (++i < 11 && get_next_line(0, &line) == 1)
	{
		if (i == 7 || i == 9)
		{
			if (!(str = ft_strrchr(line, '/')))
				return (0);
			if (!str && !(str = ft_strrchr(line, ' ')))
				return (0);
			if (i == 7)
				visu->p1 = ft_strcdup(str + 1, '.');
			else
				visu->p2 = ft_strcdup(str + 1, '.');
		}
		free(line);
	}
	return (1);
}

static int	visualizer(t_visu *visu)
{
	while (1)
	{
		if (get_score(visu) && get_next_line(0, &visu->line) != 1)
			return (-1);
		if ((!ft_strncmp(visu->line, "<got (X): [", 11)
		|| !ft_strncmp(visu->line, "<got (O): [", 11)))
		{
			if (!print_piece(visu))
				break ;
		}
		else if (!ft_strncmp(visu->line, "Plateau ", 8))
		{
			if (!get_map(visu))
				break ;
		}
		else if (!ft_strncmp(visu->line, "Piece ", 6))
		{
			if (!get_piece(visu))
				break ;
		}
		else if (!ft_strncmp(visu->line, "== O fin:", 9))
			return (finish_game(visu));
		free(visu->line);
	}
	return (1);
}

int			main(void)
{
	t_visu	visu;
	int		ret;

	visu.line = NULL;
	if (!get_player_name(&visu)
	|| (get_next_line(0, &visu.line) && !(get_map(&visu))))
		return (1);
	visu.score_len = int_len(visu.map_h * visu.map_w) + 1;
	print_init(&visu);
	free(visu.line);
	if ((ret = visualizer(&visu)) != -1)
		free(visu.line);
	ft_printf("{cursor_show}");
	return (ret != 0);
}
