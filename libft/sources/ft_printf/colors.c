/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:24:00 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/29 15:51:31 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*more_style(char *color)
{
	if (!ft_strcmp("{underline}", color))
		return ("\x1b[4m\0");
	if (!ft_strcmp("{background}", color))
		return ("\x1b[7m\0");
	if (!ft_strcmp("{clear}", color))
		return ("\x1b[2J");
	if (!ft_strcmp("{cursor_home}", color))
		return ("\x1b[H");
	if (!ft_strcmp("{cursor_save}", color))
		return ("\x1b[s");
	if (!ft_strcmp("{cursor_restore}", color))
		return ("\x1b[u");
	if (!ft_strcmp("{cursor_hide}", color))
		return ("\x1b[?25l");
	if (!ft_strcmp("{cursor_show}", color))
		return ("\x1b[?25h");
	if (!ft_strcmp("{remove_line}", color))
		return ("\x1b[2K");
	return (NULL);
}

char		*get_style(char *color)
{
	if (!ft_strcmp("{black}", color))
		return ("\x1b[0;30m\0");
	if (!ft_strcmp("{red}", color))
		return ("\x1b[0;31m\0");
	if (!ft_strcmp("{green}", color))
		return ("\x1b[0;32m\0");
	if (!ft_strcmp("{yellow}", color))
		return ("\x1b[0;33m\0");
	if (!ft_strcmp("{blue}", color))
		return ("\x1b[0;34m\0");
	if (!ft_strcmp("{purple}", color))
		return ("\x1b[0;35m\0");
	if (!ft_strcmp("{cyan}", color))
		return ("\x1b[0;36m\0");
	if (!ft_strcmp("{white}", color))
		return ("\x1b[0;37m\0");
	if (!ft_strcmp("{reset}", color))
		return ("\x1b[0m\0");
	if (!ft_strcmp("{bold}", color))
		return ("\x1b[1m\0");
	if (!ft_strcmp("{low}", color))
		return ("\x1b[2m\0");
	if (!ft_strcmp("{italic}", color))
		return ("\x1b[3m\0");
	return (more_style(color));
}

static char	*init_rgb(char *str, int r, int g, int b)
{
	const char	*seq = "\x1b[38;2;\0";
	int			rgb[4];
	int			i;
	int			j;
	int			len;

	j = 0;
	i = 0;
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	while (*seq)
		str[i++] = *seq++;
	while (j < 3)
	{
		len = 3 - !(rgb[j] / 100) - !(rgb[j] / 10);
		rgb[3] = len;
		while (len && (str[i + --len] = rgb[j] % 10 + 48))
			rgb[j] /= 10;
		i += rgb[3];
		str[i++] = j++ != 2 ? ';' : 'm';
	}
	str[i] = '\0';
	return (str);
}

char		*hex_color(char *s, char *rgb)
{
	int i;
	int	r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (*s && *s != '}')
	{
		if (i > 6 || (!(*s >= '0' && *s <= '9') && !(*s >= 'a' && *s <= 'f')))
			return (NULL);
		if (i < 2)
			r = r * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		else if (i < 4)
			g = g * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		else
			b = b * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		s++;
		i++;
	}
	if (*s != '}' || i != 6)
		return (NULL);
	return (init_rgb(rgb, r, g, b));
}

char		*dec_color(char *color, char *rgb)
{
	int r;
	int g;
	int b;

	if (*(color = atoi_jr(color + 5, &r) + 1) != ',')
		return (NULL);
	if (*(color = atoi_jr(color + 1, &g) + 1) != ',')
		return (NULL);
	if ((*(color = atoi_jr(color + 1, &b) + 1) != ')') || *(color + 1) != '}')
		return (NULL);
	if (r > 255 || b > 255 || g > 255)
		return (NULL);
	return (init_rgb(rgb, r, g, b));
}
