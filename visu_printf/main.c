/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:58:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/30 17:34:12 by tle-dieu         ###   ########.fr       */
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

int		get_piece_info(t_visu *visu)
{
	char *tmp;

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

int		get_piece(t_visu *visu)
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

int		finish_game(t_visu *visu)
{
	char	*line_x;

	line_x = NULL;
	ft_printf("{cursor_show}");
	if (get_next_line(0, &line_x) != 1 || ft_strncmp(line_x, "== X fin:", 9))
	{
		free(line_x);
		return (-1);
	}
	(void)visu;
	return (0);
}

int		get_map_info(t_visu *visu)
{
	char	*tmp;

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
	if (*tmp == '-')
	{
		sign = -1;
		tmp++;
	}
	while (*tmp >= '0' && *tmp <= '9')
		visu->y = visu->y * 10 + *tmp++ - 48;
	visu->y *= sign;
	if (*tmp && *tmp++ != ',')
		error = 0;
	if (*tmp && *tmp++ != ' ')
		error = 0;
	if (*tmp == '-')
	{
		sign = -1;
		tmp++;
	}
	while (*tmp >= '0' && *tmp <= '9')
		visu->x = visu->x * 10 + *tmp++ - 48;
	visu->x *= sign;
	if (*tmp && *tmp != ']' && !*(tmp + 1))
		error = 0;
	return (error);
}

#include <fcntl.h>

int		possible_to_place(t_visu *visu, int y, int x)
{
	int j;
	int i;
	int connect;

	j = 0;
	connect = 0;
	while (j < visu->piece_h)
	{
		i = 0;
		while (i < visu->piece_w)
		{
			if (visu->piece[j][i] == '*')
			{
				if ((x + i >= visu->map_w || y + j >= visu->map_h
							|| y + j < 0 || x + i < 0)
						|| (((visu->map[y + j][x + i] != visu->actual_p
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

int place_piece(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	usleep(10000);
	if (!info_place(visu))
		return (0);
	if (!possible_to_place(visu, visu->y, visu->x))
		return (1);
	while (j < visu->piece_h)
	{
		i = 0;
		while (i < visu->piece_w)
		{
			if (visu->piece[j][i] == '*')
			{
				ft_printf("\033[%d;%dH", 12 + visu->y + j, (visu->x + i) * 2 + 4);
				if (visu->actual_p == 'O')
					ft_printf("{#c3282f}"C_PLAY" ");
				else if (visu->actual_p == 'X')
					ft_printf("{#3e92cc}"C_PLAY" ");
			}
			++i;
		}
		++j;
	}
	ft_printf("{reset}");
	ft_printf("\033[%d;0H", 12 + visu->map_h);
	return (1);
}

void	print_map(t_visu *visu)
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

int		main(void)
{
	t_visu	visu;

	visu.line = NULL;
	visu.fd = open("/dev/ttys001", O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	if (!get_player_name(&visu))
		return (1);
	ft_printf("{cursor_hide}");
	ft_printf("{clear}");
	ft_printf("{remove_line}");
	ft_printf("\033[2;0H");
	print_title();
	if (get_next_line(0, &visu.line))
		if (!(get_map(&visu)))
			return (1);
	ft_printf("\033[12;0H");
	print_map(&visu);
	while (1)
	{
		if (get_next_line(0, &visu.line) != 1)
			return (1);
		if (!ft_strncmp(visu.line, "<got (X): [", 11)
				|| !ft_strncmp(visu.line, "<got (O): [", 11))
		{
			if (!place_piece(&visu))
				return (1);
		}
		else if (!ft_strncmp(visu.line, "Plateau ", 8))
		{
			if (!(get_map(&visu)))
				return (1);
		}
		else if (!ft_strncmp(visu.line, "== O fin:", 9))
		{
			if (!(finish_game(&visu)))
				return (1);
		}
		else if (!(ft_strncmp(visu.line, "Piece ", 6)))
		{
			if (!(get_piece(&visu)))
				return (1);
		}
		else if (ft_strcmp(visu.line, "Player with O: error on input")
				&& ft_strcmp(visu.line, "Player with X: error on input"))
			return (1);
	}
	ft_printf("{cursor_show}");
	return (0);
}
