/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:30:33 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/29 18:10:58 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>

int		main(void)
{
	int i;

	i = 0;
	ft_printf("{cursor_hide}");
	ft_printf("\\033[%0;0H");
	ft_printf("{clear}");
	ft_printf("{remove_line}");
	ft_printf("{cursor_show}");
	ft_printf("{reset}");
	while (1)
		;
}
