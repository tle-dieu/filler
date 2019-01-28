/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:09:35 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/28 13:10:32 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "../libft/includes/libft.h"

void	read_map(t_visu *p)
{
	char *line;

	ft_printf("ok\n");
	while (get_next_line(0, &line) == 1)
		ft_printf("%s\n", line);
}

int		main(void)
{
	t_visu	p;

	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, WIDTH, HEIGHT, "Filler Visualizer");
	p.img = mlx_new_image(p.mlx, WIDTH, HEIGHT);
	read_map(&p);
	mlx_loop(p.mlx);
	/* p.img = mlx_xpm_file_to_image(p.mlx, "test.xpm", &n, &r); */
	/* mlx_put_image_to_window(p.mlx, p.win, p.img, 0, 0); */
	/* mlx_loop(p.mlx); */
}
