/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:45:57 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/28 11:59:14 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "mlx.h"
# define WIDTH 1280
# define HEIGHT 720

typedef struct	s_visu
{
	void	*mlx;
	void	*win;
	void	*img;
}				t_visu;

#endif
