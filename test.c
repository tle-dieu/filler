/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:30:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 15:42:31 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		main(void)
{
	struct winsize w;
	int i;
	int j;

	ft_printf("{clear}");
	ft_printf("{cursor_hide}");
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ft_printf("\033[%d;%dH🌘", 5, w.ws_row - 5);
	ft_printf("\033[%d;%dH🌍", w.ws_row, 0);
	j = w.ws_row - 1;
	i = 1;
	while (j > 5)
	{
		if (i > 1)
			ft_printf("{remove_line}");
		ft_printf("\033[%d;%dH", j--, i++);
		ft_printf("🚀");
		usleep(40000);
	}
	ft_printf("\n");
	return (0);
}
