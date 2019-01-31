/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:58:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:29 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visualizer.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define BG(x, color) "{"color"}{background}%"x"c"

void	print_title(t_visu *visu)
{
	ft_printf("\033[%9;%dH", visu->print_width);
	ft_printf("\n{#c3282f}{bold}%-*s{#ffffff}{bold}VS{#3e92cc}{bold}%*s\n", visu->map_w - 2, visu->p1, visu->map_w - 2, visu->p2);
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
	if (visu->p1_score > visu->p2_score)
		ft_printf("\n{green}{bold}%s won\n{reset}", visu->p1);	
	else if (visu->p1_score < visu->p2_score)
		ft_printf("\n{green}{bold}%s won\n{reset}", visu->p2);	
	else
		ft_printf("\n{white}{bold}equality\n{reset}");	
	if (get_next_line(0, &line_x) != 1 || ft_strncmp(line_x, "== X fin:", 9))
	{
		free(line_x);
		return (-1);
	}
	(void)visu;
	return (0);
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
				visu->p1 = ft_strcdup(str + 1, '.');
			else
				visu->p2 = ft_strcdup(str + 1, '.');
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

void	print_score(t_visu *visu)
{
	int width;
	int map_size;
	int p1;
	int p2;
	
	width = visu->map_w * 2 - 10;
	map_size = visu->map_h * visu->map_w / width;

	p1 = visu->p1_score / map_size;
	p2 = visu->p2_score / map_size;
	ft_printf("\033[%d;%dH", visu->map_h + 13, visu->print_width);
	ft_printf("\n  {#c3282f}%5d ", visu->p1_score);
	ft_printf("{#c3282f}{background}%*c", p1, ' ');
	if ((width  - p1 - p2 > 0))
		ft_printf("{#484848}{background}%*c", width  - p1 - p2, ' ');
	ft_printf("{#3e92cc}{background}%*c", p2, ' ');
	ft_printf("{reset}{#3e92cc} %-5d\n{reset}", visu->p2_score);
}

void	get_score(t_visu *visu)
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
			if (visu->map[y][x] == 'x' || visu->map[y][x] == 'X' )
				++visu->p2_score;	
			else if (visu->map[y][x] == 'o' || visu->map[y][x] == 'O' )
				++visu->p1_score;	
			++x;
		}
		++y;	
	}
	print_score(visu);
}

void	print_background(t_visu *visu)
{
	int i;

	i = 0;
	while (i++ < visu->w.ws_col)
		ft_printf("{#232323}{background}%*c", visu->w.ws_row, ' ');
	ft_printf("{reset}");
}

int		main(void)
{
	t_visu	visu;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &visu.w);
	visu.line = NULL;
	visu.fd = open("/dev/ttys001", O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	if (!get_player_name(&visu))
		return (1);
	ft_printf("{cursor_hide}{clear}{remove_line}");
	print_background(&visu);
	if (get_next_line(0, &visu.line) && !(get_map(&visu)))
			return (1);
	print_title(&visu);
	ft_printf("\033[12;0H");
	print_map(&visu);
	while (1)
	{
		get_score(&visu);
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
			{
				ft_printf("{cursor_show}");
				return (0);
			}
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
}
