/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:58:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/30 01:10:09 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visualizer.h"
#include <stdlib.h>
#include <unistd.h>
#define BG(x, color) "{"color"}{background}%"x"c"

void	print_title()
{
	char c;

	c = ' ';
	ft_printf(BG("3","#000000")BG("12","#f44336")BG("1", "#000000")BG("6","#f44336")BG("1", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("12","#f44336")BG("1", "#000000")BG("14", "#f44336")"\n",c,c,c,c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("12","#f44336")BG("1", "#000000")BG("6","#f44336")BG("1", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("12","#f44336")BG("1", "#000000")BG("14", "#f44336")"\n",c,c,c,c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("6","#f44336")BG("14","#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("3", "#000000")BG("5","#f44336")"\n",c,c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("9","#f44336")BG("4","#000000")BG("6","#f44336")BG("1", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("9","#f44336")BG("4", "#000000")BG("14","#f44336")"\n",c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("9","#f44336")BG("4","#000000")BG("6","#f44336")BG("1", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("9","#f44336")BG("4", "#000000")BG("14","#f44336")"\n",c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("6","#f44336")BG("7","#000000")BG("6","#f44336")BG("1", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("7", "#000000")BG("6","#f44336")BG("2","#000000")BG("6","#f44336")"\n",c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("6","#f44336")BG("7","#000000")BG("6","#f44336")BG("1", "#000000")BG("12", "#f44336")BG("1", "#000000")BG("12","#f44336")BG("1", "#000000")BG("12","#f44336")BG("1", "#000000")BG("6","#f44336")BG("3","#000000")BG("6","#f44336")"\n",c,c,c,c,c,c,c,c,c,c);
	ft_printf(BG("3","#000000")BG("6","#f44336")BG("7","#000000")BG("6","#f44336")BG("1", "#000000")BG("12", "#f44336")BG("1", "#000000")BG("12","#f44336")BG("1", "#000000")BG("12","#f44336")BG("1", "#000000")BG("6","#f44336")BG("3","#000000")BG("6","#f44336")"\n",c,c,c,c,c,c,c,c,c,c,c,c);
	ft_printf("{reset}\n");
}

void		free_content(char ***content, int height_map)
{
	int i;

	i = 0;
	if (content)
	{
		while (i < height_map)
			free((*content)[i++]);
		free(*content);
		*content = NULL;
	}
}

int		finish_game(t_visu *visu, char *line_o)
{
	char	*line_x;

	line_x = NULL;
	ft_printf("finish line: %s\n", line_o);
	if (ft_strncmp(line_o, "== O fin:", 9)
			|| get_next_line(0, &line_x) != 1 || ft_strncmp(line_x, "== X fin:", 9))
	{
		ft_printf("erreur finish\n");
		/* free(line_o); */
		free(line_x);
		return (-1);
	}
	(void)visu;
	return (0);
}

int		get_map_info(t_visu *visu)
{
	char	*line;
	char	*tmp;
	int		ret;

	visu->width_map = 0;
	visu->height_map = 0;
	line = NULL;
	ret = 0;
	if (get_next_line(0, &line) != 1)
		return (-1);
	visu->line = line;
	if (!ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9')
			visu->height_map = visu->height_map * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			visu->height_map = 0;
		while (*tmp >= '0' && *tmp <= '9')
			visu->width_map = visu->width_map * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			visu->width_map = 0;
	}
	else
		return (finish_game(visu, line));
	free(line);
	return (1);
}

int		get_map(t_visu *visu)
{
	char	*line;
	int		i;
	int		ret;

	i = 0;
	line = NULL;
	visu->map = NULL;
	if ((ret = get_map_info(visu)) != 1)
		return (ret);
	if (get_next_line(0, &line) != 1
			|| !(visu->map = (char **)malloc(sizeof(char *) * visu->height_map)))
	{
		free(line);
		return (-1);
	}
	free(line);
	while (i < visu->height_map && get_next_line(0, &line) == 1)
	{
		if ((int)ft_strlen(line) - 4 != visu->width_map
				|| !(visu->map[i++] = ft_strdup(line + 4)))
		{
			free(line);
			free_content(&visu->map, i);
			return (-1);
		}
		free(line);
	}
	return (i == visu->height_map);
}

int		get_player_name(t_visu *visu)
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
				visu->p1 = ft_strdup(str + 1);
			else
				visu->p2 = ft_strdup(str + 1);
		}
		free(line);
	}
	return (1);
}

void	print_map(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	while (j < visu->height_map)
	{
		i = 0;
		ft_printf("   ");
		while (i < visu->width_map)
		{
			if (visu->map[j][i] == 'O')
				ft_printf("{#c3282f}▩ ");
			else if (visu->map[j][i] == 'X')
				ft_printf("{#3e92cc}▩ ");
			else
				ft_printf("{#484848}▩ ");
			++i;
		}
		ft_printf("\n");
		++j;
	}
	ft_printf("{reset}");
	ft_printf("\n");
}

int		get_out(int error, t_visu *visu)
{
	int		j;
	int		height;
	char	*tmp;

	j = 0;
	height = 0;
	if (((visu->line && error == -1) || (get_next_line(0, &visu->line) == 1)) && !(ft_strncmp(visu->line, "Piece ", 6)))
	{
		tmp = visu->line + 6;
		while (*tmp >= '0' && *tmp <= '9')
			height = height * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			height = 0;
		while (*tmp >= '0' && *tmp <= '9')
			tmp++;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			height = 0;
	}
	free(visu->line);
	visu->line = NULL;
	if (!height)
		return (0);
	while (j++ - 1 < height && get_next_line(0, &visu->line))
	{
		free(visu->line);
		visu->line = NULL;
	}
	return (1);
}

int		main(void)
{
	int		error;
	t_visu	visu;
	int		i;

	i = 0;
	visu.line = NULL;
	if (!get_player_name(&visu))
		return (1);
	ft_printf("{cursor_hide}");
	ft_printf("{clear}");
	ft_printf("{remove_line}");
	ft_printf("\033[2;0H");
	print_title();
	while ((error = get_map(&visu)))
	{
		ft_printf("\033[12;0H");
		print_map(&visu);
		if (!get_out(error, &visu))
			return (1);
		usleep(10000);
	}
	ft_printf("{cursor_show}");
	return (0);
}
