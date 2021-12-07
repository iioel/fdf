/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:13:00 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/07 20:27:52 by ycornamu         ###   ########.fr       */
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

void	rotate(double *x, double *y, double *z, t_obj *obj)
{
	double	point[3][1];

	point[0][0] = *x;
	point[1][0] = *y;
	point[2][0] = *z;
	mtx_mul(obj->rotx, point);
	mtx_mul(obj->roty, point);
	mtx_mul(obj->rotz, point);
	*x = point[0][0];
	*y = point[1][0];
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
	rotate(&s_x, &s_y, &s_z, w->obj);
	d.x = (int)s_x + w->width / 2;
	d.y = (int)s_y + w->height / 2;
	set_hsv(d.hsv_c, 60 + z * 26, 40, 100);
	//set_hsv(d.hsv_c, 60, 0, 100);
	return (d);
}

void	line_put(t_window *w, t_pixel a, t_pixel b)
{
	int		steps, i;
	double	x, y, x_i, y_i, hsv_c[3];
	double	hsv_i[3];
    x = a.x;
    y = a.y;
	set_hsv_d(hsv_c, a.hsv_c[0], a.hsv_c[1], a.hsv_c[2]);
	if (ft_abs(b.x - a.x) > ft_abs(b.y - a.y))
		steps = ft_abs(b.x - a.x);
	else
		steps = ft_abs(b.y - a.y);
	x_i = (b.x - a.x) / (double)steps;
	y_i = (b.y - a.y) / (double)steps;
	set_hsv_d(hsv_i, (b.hsv_c[0] - a.hsv_c[0]) / (double)steps,
			(b.hsv_c[1] - a.hsv_c[1]) / (double)steps,
			(b.hsv_c[2] - a.hsv_c[2]) / (double)steps);
	i = 0;
	while (i < steps)
	{
		x += x_i;
		y += y_i;
		hsv_c[0] += hsv_i[0];
		hsv_c[1] += hsv_i[1];
		hsv_c[2] += hsv_i[2];
		mlx_pixel_put_img(w->obj->img, (int)x, (int)y, hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		i++;
	}
}
