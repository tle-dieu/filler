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
	ft_printf("\x1b[48;2;255;0;0m Background blackcolor: \n");
	ft_printf("\033[38;2;255;255;0m{italic}Foreground color: red\n");
}
