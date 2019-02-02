/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:55:10 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/02 13:41:04 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <stdlib.h>

char	*atoi_jr_v2(char *s, int *nb)
{
	int sign;

	sign = 1;
	*nb = 0;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		*nb = *nb * 10 + *s++ - 48;
	*nb = *nb * sign;
	return (s);
}

int		int_len(int nb)
{
	int len;

	len = 1;
	while (nb /= 10)
		len++;
	return (len);
}

void	free_content(char ***content, int height_map)
{
	int i;

	i = 0;
	if (content && *content)
	{
		while (i < height_map)
			free((*content)[i++]);
		free(*content);
		*content = NULL;
	}
}
