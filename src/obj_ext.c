/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:53:05 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/07 20:53:38 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	write_pixel(t_window *w, t_obj *obj, int x, int y)
{
	t_pixel	p;

	p = get_pixel(w, x, y, obj->grid[x + y * obj->width]);
	mlx_pixel_put_img(obj->img, p.x, p.y,
		hsv2rgb(p.hsv_c[0], p.hsv_c[1], p.hsv_c[2]));
	if (x != 0)
		line_put(w, p,
			get_pixel(w, x - 1, y, obj->grid[x - 1 + y * obj->width]));
	if (y != 0)
		line_put(w, p,
			get_pixel(w, x, y - 1, obj->grid[x + (y - 1) * obj->width]));
}

void	render_obj(t_window *w)
{
	int		x;
	int		y;
	t_obj	*obj;

	x = 0;
	obj = w->obj;
	if (obj->img)
		mlx_destroy_image(w->mlx, obj->img->img);
	obj->img = create_image(w);
	while (x < obj->width)
	{
		y = 0;
		while (y < obj->length)
		{
			write_pixel(w, obj, x, y);
			y++;
		}
		x++;
	}
}
