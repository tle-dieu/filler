/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:39:38 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/28 22:42:08 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_content(char ***content, int height)
{
	int i;

	i = 0;
	if (content)
	{
		while (i < height)
			free((*content)[i++]);
		free(*content);
		*content = NULL;
	}
}

long long	get_norm(int y1, int y2, int x1, int x2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
