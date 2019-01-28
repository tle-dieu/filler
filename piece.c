/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:54:38 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/28 22:41:22 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_piece_info(t_piece *piece)
{
	char *line;
	char *tmp;

	line = NULL;
	piece->height = 0;
	piece->width = 0;
	if (get_next_line(0, &line) == 1 && !(ft_strncmp(line, "Piece ", 6)))
	{
		tmp = line + 6;
		while (*tmp >= '0' && *tmp <= '9')
			piece->height = piece->height * 10 + *tmp++ - 48;
		if (*tmp && *tmp++ != ' ')
			piece->height = 0;
		while (*tmp >= '0' && *tmp <= '9')
			piece->width = piece->width * 10 + *tmp++ - 48;
		if (*tmp && *tmp != ':' && !*(tmp + 1))
			piece->width = 0;
	}
	free(line);
	return (piece->width && piece->height);
}

int		create_piece(t_piece *piece)
{
	int		j;
	int		i;
	int		stars;
	char	*line;

	j = 0;
	i = 0;
	stars = 0;
	line = NULL;
	while (j < piece->height && get_next_line(0, &line))
	{
		i = 0;
		while (line[i])
			if (line[i++] == '*' && ++stars == 1)
				piece->first = j;
		piece->content[j++] = line;
		if ((j == piece->height && !stars) || i != piece->width)
		{
			free_content(&piece->content, j);
			return (0);
		}
	}
	return (1);
}

int		get_piece(t_piece *piece)
{
	char	*line;

	line = NULL;
	if (!get_piece_info(piece)
	|| !(piece->content = (char **)malloc(sizeof(char *) * piece->height)))
	{
		free(line);
		return (0);
	}
	return (create_piece(piece));
}
