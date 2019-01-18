/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:17:31 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/18 17:13:18 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include <fcntl.h> // a retirer
#include <stdlib.h>
#define PLAYER_NAME 17

int		get_piece_info(t_piece *piece)
{
	char *line;
	char *tmp;

	line = NULL;
	piece->height = 0;
	piece->width = 0;
	if (get_next_line(0, &line) == 1 && !(ft_strncmp(line,"Piece ", 6)))
	{
		tmp = line + 6;
		while (*tmp >= '0' && *tmp <= '9' )
			piece->height = piece->height * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			piece->height = 0;
		while (*tmp >= '0' && *tmp <= '9' )
			piece->width = piece->width * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			piece->width = 0;
	}
	free(line);
	ft_dprintf(piece->fd, "fin get_piece_info\n");
	return (piece->width && piece->height);
}

int		get_piece(t_piece *piece)
{
	char	*line;
	int		j;
	int		i;
	int		stars;

	j = 0;
	i = 0;
	stars = 0;
	line = NULL;
	if (!get_piece_info(piece) || !(piece->content = (char **)malloc(sizeof(char *) * piece->height)))
	{
		free(line);
		return (0);
	}
	while (j < piece->height && get_next_line(0, &line))
	{
		i = 0;
		while (line[i])
			if (line[i++] == '*' && ++stars == 1)
				piece->first = j;
		piece->content[j++] = line;
	}
	ft_dprintf(piece->fd, "fin get_piece\n");
	return (stars);
}

int		get_map_info(t_map *map)
{
	char	*line;
	char	*tmp;

	map->x_max = 0;
	map->y_max = 0;
	line = NULL;
	if (get_next_line(0, &line) == 1 && !ft_strncmp(line, "Plateau ", 8))
	{
		tmp = line + 8;
		while (*tmp >= '0' && *tmp <= '9' )
			map->y_max = map->y_max * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			map->y_max = 0;
		while (*tmp >= '0' && *tmp <= '9' )
			map->x_max = map->x_max * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			map->x_max = 0;
	}
	free(line);
	ft_dprintf(map->fd, "fin get_map_info\n");
	return (map->x_max && map->y_max);
}

int		get_map(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	map->content = NULL;
	if (!get_map_info(map) || get_next_line(0, &line) != 1
			|| !(map->content = (char **)malloc(sizeof(char *) * map->y_max)))
	{
		free(line);
		return (0);
	}
	while (i < map->y_max && get_next_line(0, &line) == 1)
		map->content[i++] = line + 4; // free content en cas d'erreur / pareil pour get_piece
	i = 0;
	ft_dprintf(map->fd, "fin get_map\n");
	return (1);
}

int		get_player_info(t_map *map)
{
	char	*line;
	int		len;

	line = NULL;
	map->order = 0;
	if (get_next_line(0, &line) == 1 && (len = ft_strlen(line)) >= PLAYER_NAME + 16
			&& (!ft_strncmp(line, "$$$ exec p2 : [", 15) || !ft_strncmp(line, "$$$ exec p1 : [", 15))
			&& !ft_strcmp(line + len - PLAYER_NAME, "/tle-dieu.filler]"))
	{
		map->order = line[10] - 48;
		map->my_sign = map->order == 1 ? 'O' : 'X';
		map->adv_sign = map->order == 1 ? 'X' : 'O';
		ft_dprintf(map->fd, "player info: %s\n", line);
	}
	free(line);
	ft_dprintf(map->fd, "fin get_player_info\n");
	return (map->order);
}

int		possible_to_place(t_map *map, t_piece *piece, int y, int x)
{
	int	j;
	int	i;
	int	connect;

	j = piece->first;
	connect = 0;
	/* ft_dprintf(map->fd, "possible_to_place: y: %d x: %d\n", y, x); */
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			if (piece->content[j][i] == '*')
			{
				/* ft_dprintf(map->fd, "stars find: piece->content[%d][%d]\n", j, i); */
				/* ft_dprintf(map->fd, "j + y = %d i + x = %d\n", j + y, i + x); */
				if (y + j < 0 || y + j >= map->y_max || x + i < 0 || x + i >= map->x_max)
				{
					/* ft_dprintf(map->fd, "hors map\n"); */
					return (0);
				}
				/* ft_dprintf(map->fd, "content == %c\n", map->content[y + j][x + i]); */
				if (map->content[y + j][x + i] != map->my_sign || ++connect > 1)
				{
					if (map->content[y + j][x + i] != '.')
					{
						return (0);
					}
				}
			}	
			i++;
		}
		j++;
	}
	return (connect);
}

int		place_piece(t_map *map, t_piece *piece)
{
	int x;
	int y;

	ft_dprintf(map->fd, "\n{cyan}debut place piece{reset}\n");
	y = -piece->height + 1;
	while (y < map->y_max)
	{
		x = -piece->width + 1;
		while (x < map->x_max)
		{
			if (possible_to_place(map, piece, y, x))
			{
				ft_dprintf(map->fd, "coord: y = %d x = %d\n", y, x);
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			++x;
		}
		++y;
	}
	ft_printf("0 0\n");
	return (0);
}

int		main(void)
{
	t_map	map;
	t_piece piece;
	int		j;
	int		loop;

	loop = 1;
	map.content = NULL;
	map.fd = open("./result/read.txt",  O_TRUNC | O_WRONLY | O_CREAT | O_APPEND);
	piece.fd = map.fd;
	ft_dprintf(map.fd, "{green}----------INFO MAP----------{reset}\n\n");
	if (!get_player_info(&map))
		return (1);
	ft_dprintf(map.fd, "order: %d\nmy sign: %c\nadv sign: %c\n\n", map.order, map.my_sign, map.adv_sign);
	while (1)
	{
		ft_dprintf(map.fd, "{cyan}----------TOUR %d----------{reset}\n", loop++);
		if (!get_map(&map))
		{
			ft_dprintf(map.fd, "error map\n");
			return (1);
		}
		j = 0;
		ft_dprintf(map.fd, "{#de6864}-----MAP-----{reset}\n");
		ft_dprintf(map.fd, "    01234567890123456\n");
		while (j < map.y_max)
		{
			ft_dprintf(map.fd, "%.3d ", j);
			ft_dprintf(map.fd, "%s\n", map.content[j++]);
		}
		if (!get_piece(&piece))
		{
			ft_dprintf(map.fd, "error piece\n");
			return (1);
		}
		j = 0;
		ft_dprintf(map.fd, "{#fb3268}-----PIECE-----{reset}\n");
		while (j < piece.height)
			ft_dprintf(map.fd, "%s\n", piece.content[j++]);
		if (!place_piece(&map, &piece))
		{
			ft_dprintf(map.fd, "error place piece\n");
			return (1);
		}
		ft_dprintf(map.fd, "piece placee\n\n");
	}
	return (0);
}
