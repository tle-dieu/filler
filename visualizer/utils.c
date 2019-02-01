/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:55:10 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 20:02:39 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <stdlib.h>

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
