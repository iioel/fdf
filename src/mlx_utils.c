/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:13:00 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 11:47:36 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color)
{
	char	*p_loc;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		p_loc = img->addr + (y * img->line_bytes + x * (img->pixel_bits / 8));
		*(unsigned int *)p_loc = color;
	}
}

void	rotate(double *x, double *y, double *z, t_window *w)
{
	double	point[3][1];
	double	zoom;
	t_obj	*obj;

	obj = w->obj;
	point[0][0] = *x;
	point[1][0] = *y;
	point[2][0] = *z;
	mtx_mul(obj->rotx, point);
	mtx_mul(obj->roty, point);
	mtx_mul(obj->rotz, point);
	zoom = 1;
	if (obj->projected)
		zoom = w->scale / ((double)obj->distance - point[2][0]);
	*x = point[0][0] * zoom;
	*y = point[1][0] * zoom;
	*z = point[2][0];
}

t_pixel	get_pixel(t_window *w, int x, int y, int z)
{
	t_pixel	d;
	double	s_x;
	double	s_y;
	double	s_z;

	s_x = ((double)x - w->obj->width / 2) * w->scale;
	s_y = ((double)y - w->obj->length / 2) * w->scale;
	s_z = ((double)z - w->obj->height / 2) * w->scale;
	rotate(&s_x, &s_y, &s_z, w);
	d.x = (int)s_x + w->width / 2 + w->offx;
	d.y = (int)s_y + w->height / 2 + w->offy;
	set_hsv(d.hsv_c, 60 + z * 26, 40, 100);
	return (d);
}
