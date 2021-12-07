/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:31:12 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/07 20:51:45 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_line	*create_line(t_pixel a, t_pixel b)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (! line)
		return (NULL);
	line->x = a.x;
	line->y = a.y;
	if (ft_abs(b.x - a.x) > ft_abs(b.y - a.y))
		line->steps = ft_abs(b.x - a.x);
	else
		line->steps = ft_abs(b.y - a.y);
	line->x_i = (b.x - a.x) / (double)line->steps;
	line->y_i = (b.y - a.y) / (double)line->steps;
	set_hsv_d(line->hsv_c, a.hsv_c[0], a.hsv_c[1], a.hsv_c[2]);
	set_hsv_d(line->hsv_c_i, (b.hsv_c[0] - a.hsv_c[0]) / (double)line->steps,
		(b.hsv_c[1] - a.hsv_c[1]) / (double)line->steps,
		(b.hsv_c[2] - a.hsv_c[2]) / (double)line->steps);
	return (line);
}

void	line_put(t_window *w, t_pixel a, t_pixel b)
{
	t_line	*line;
	int		i;

	line = create_line(a, b);
	i = 0;
	while (i < line->steps)
	{
		line->x += line->x_i;
		line->y += line->y_i;
		line->hsv_c[0] += line->hsv_c_i[0];
		line->hsv_c[1] += line->hsv_c_i[1];
		line->hsv_c[2] += line->hsv_c_i[2];
		mlx_pixel_put_img(w->obj->img, (int)line->x, (int)line->y,
			hsv2rgb(line->hsv_c[0], line->hsv_c[1], line->hsv_c[2]));
		i++;
	}
	free(line);
}
