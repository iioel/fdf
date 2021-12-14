/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:50:22 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 14:09:10 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_obj	*create_obj(char *file)
{
	t_obj	*obj;

	obj = ft_calloc(1, sizeof(t_obj));
	if (! obj)
		return (NULL);
	obj->height = 0;
	obj->width = 0;
	obj->length = 0;
	obj->anglx = 0;
	obj->angly = 0;
	obj->anglz = 0;
	obj->grid = NULL;
	obj->projected = 0;
	obj->distance = 2;
	obj->img = NULL;
	if (read_file(file, obj))
	{
		free(obj);
		return (NULL);
	}
	add_angles(35, 45, 0, obj);
	return (obj);
}

void	display_obj(t_window *w)
{
	mlx_clear_window(w->mlx, w->w);
	mlx_put_image_to_window(w->mlx, w->w, w->obj->img->img, 0, 0);
}

void	update_mtx(t_obj *obj)
{
	double	a;
	double	b;
	double	c;

	a = obj->anglx * M_PI / 180;
	b = obj->angly * M_PI / 180;
	c = obj->anglz * M_PI / 180;
	mtx_setline(&obj->rotx[0], 1, 0, 0);
	mtx_setline(&obj->rotx[1], 0, cos(a), -sin(a));
	mtx_setline(&obj->rotx[2], 0, sin(a), cos(a));
	mtx_setline(&obj->roty[0], cos(b), 0, sin(b));
	mtx_setline(&obj->roty[1], 0, 1, 0);
	mtx_setline(&obj->roty[2], -sin(b), 0, cos(b));
	mtx_setline(&obj->rotz[0], cos(c), -sin(c), 0);
	mtx_setline(&obj->rotz[1], sin(c), cos(c), 0);
	mtx_setline(&obj->rotz[2], 0, 0, 1);
}

void	add_angles(int alpha, int beta, int gamma, t_obj *obj)
{
	obj->anglx += alpha;
	obj->angly += beta;
	obj->anglz += gamma;
	update_mtx(obj);
}

void	clean_obj(t_obj *obj)
{
	free(obj->img);
	free(obj->grid);
	free(obj);
}
