/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:58:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/30 07:04:02 by tle-dieu         ###   ########.fr       */
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

int		get_piece_info(t_visu *visu, int replace)
{
	char *line;
	char *tmp;

	line = (replace ? visu->line : NULL);
	visu->piece_h = 0;
	visu->piece_w = 0;
	if (replace)
		ft_printf("line: %s\n", visu->line);
	if ((replace || get_next_line(0, &line) == 1) && !(ft_strncmp(line, "Piece ", 6)))
	{
		tmp = line + 6;
		while (*tmp >= '0' && *tmp <= '9')
			visu->piece_h = visu->piece_h * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			visu->piece_h = 0;
		while (*tmp >= '0' && *tmp <= '9')
			visu->piece_w = visu->piece_w * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			visu->piece_w = 0;
	}
	if (line && line == visu->line)
		visu->line = NULL;
	ft_printf("%s\n", line);
	free(line);
	return (visu->piece_w && visu->piece_h);
}

int		get_piece(t_visu *visu, int replace)
{
	int		j;
	char	*line;

	j = 0;
	line = NULL;
	ft_printf("GET_PIECE\n");
	if (!get_piece_info(visu, replace)
	|| !(visu->piece = (char **)malloc(sizeof(char *) * visu->piece_h)))
	{
		free(line);
		return (0);
	}
	while (j < visu->piece_h && get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		visu->piece[j++] = line;
		if ((int)ft_strlen(line) != visu->piece_w)
		{
			free_content(&visu->piece, j);
			return (0);
		}
	}
	return (1);
}

int		finish_game(t_visu *visu, char *line_o)
{
	char	*line_x;

	line_x = NULL;
	ft_printf("FINISH\n");
	ft_printf("%s\n", line_o);
	if (ft_strncmp(line_o, "Piece ", 6) && (ft_strncmp(line_o, "== O fin:", 9) || get_next_line(0, &line_x) != 1 || ft_strncmp(line_x, "== X fin:", 9)))
	{
		ft_printf("error finish\n");
		ft_printf("%s\n", line_x);
		/* free(line_o); */
		free(line_x);
		return (-1);
	}
	else if (!(ft_strncmp(line_o, "Piece ", 6)))
	{
		visu->line = line_o;
		free_content(&visu->piece, visu->piece_h);
		get_piece(visu, 1);
		return (1);
	}
	else
		return (-1);
	(void)visu;
	return (0);
}

int		get_map_info(t_visu *visu)
{
	char	*line;
	char	*tmp;
	int		ret;

	visu->map_w = 0;
	visu->map_h = 0;
	line = NULL;
	ret = 0;
	if (get_next_line(0, &line) != 1)
		return (-1);
	ft_printf("%s\n", line);
	visu->line = line;
	if (!ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9')
			visu->map_h = visu->map_h * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			visu->map_h = 0;
		while (*tmp >= '0' && *tmp <= '9')
			visu->map_w = visu->map_w * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			visu->map_w = 0;
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
	ft_printf("GET_MAP\n");
	if ((ret = get_map_info(visu)) != 1)
		return (ret);
	if (get_next_line(0, &line) != 1
			|| !(visu->map = (char **)malloc(sizeof(char *) * visu->map_h)))
	{
		ft_printf("%s\n", line);
		free(line);
		return (-1);
	}
	ft_printf("%s\n", line);
	free(line);
	while (i < visu->map_h && get_next_line(0, &line) == 1)
	{
		ft_printf("%s\n", line);
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
	/* ft_printf("\033[40;0H"); */
	/* ft_printf("{reset}"); */
	/* ft_printf("\n"); */
}

int		info_place(t_visu *visu)
{
	char	*line;
	char	*tmp;
	int		error;
	int		sign;

	line = NULL;
	error = 1;
	visu->y = 0;
	visu->x = 0;
	sign = 1;
	ft_printf("INFO_PLACE\n");
	if (get_next_line(0, &line) != 1)
		return (0);
	ft_printf("%s\n", line);
	if (!ft_strncmp(line, "<got (X): [", 11) || !ft_strncmp(line, "<got (O): [", 11))
	{
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
	}
	free(line);
	return (error);
}

int place_piece(t_visu *visu)
{
	int i;
	int j;

	j = 0;
	if (!info_place(visu))
		return (0);
	while (j < visu->piece_h)
	{
		i = 0;
		while (i < visu->piece_w)
		{
			if (visu->piece[j][i] == '*')
			{
				/* ft_printf("\033[%d;%dH", 12 + visu->y + j, (visu->x + i) * 2 + 1 + 3); */
				/* if (visu->actual_p == 'O') */
					/* ft_printf("{#c3282f}▩ "); */
				/* else if (visu->actual_p == 'X') */
					/* ft_printf("{#3e92cc}▩ "); */
			}
			++i;
		}
		++j;
	}
	ft_printf("{reset}");
	return (1);
}

int		main(void)
{
	t_visu	visu;
	int		error;

	error = 0;
	visu.line = NULL;
	if (!get_player_name(&visu))
		return (1);
	ft_printf("{cursor_hide}");
	ft_printf("{clear}");
	ft_printf("{remove_line}");
	ft_printf("\033[2;0H");
	print_title();
	if (!(get_map(&visu)))
		return (1);
	ft_printf("\033[12;0H");
	/* print_map(&visu); */
	ft_printf("\033[50;0H");
	while (1)
	{
		if (!get_piece(&visu, 0))
		{
			ft_printf("error piece\n");
			error = -1;
			break ;
		}
		if (!place_piece(&visu))
		{
			ft_printf("error place\n");
			error = -1;
			break ;
		}
		if (!(get_map(&visu)))
			return (1);
		usleep(10000);
	}
	ft_printf("{cursor_show}");
	return (error);
}
