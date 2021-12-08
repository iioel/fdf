/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:53:10 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/08 23:12:04 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	catch_key(int t, t_window *w)
{
//	printf("key : %d\n", t);
	if (t == 53 || t == 65307) // ESC
	{
		mlx_destroy_window(w->mlx, w->w);
		exit(0);
	}
	else if (t == 8) // c
		mlx_clear_window(w->mlx, w->w);
	else if (t == 126 || t == 65362) // UP
		w->obj->distance *= 1.05;
	else if (t == 125 || t == 65364) // DOWN
		w->obj->distance *= (1 / 1.05);
	else if (t == 13 || t == 119) // w
		w->obj->anglx += 2;
	else if (t == 0 || t == 97) // a
		w->obj->angly -= 2;
	else if (t == 1 || t == 115) // s
		w->obj->anglx -= 2;
	else if (t == 2 || t == 100) // d
		w->obj->angly += 2;
	else if (t == 12 || t == 113) // q
		w->obj->anglz -= 2;
	else if (t == 14 || t == 101) // e
		w->obj->anglz += 2;
	else if (t == 7 || t == 120) // x
		w->obj->anglx = 0;
	else if (t == 16 || t == 121) // y
		w->obj->angly = 0;
	else if (t == 6 || t == 122) // z
		w->obj->anglz = 0;
	else if (t == 34) // i
	{
		w->obj->anglx = 45;
		w->obj->angly = 35;
		w->obj->anglz = -30;
		if (w->obj->projected)
		{
			w->obj->projected = 0;
			w->scale /= 7;
		}
	}
	else if (t == 35) // p
	{
		w->obj->projected = 1;
		w->scale = w->scale / 20;
	}
	update_mtx(w->obj);
	render_obj(w);
	display_obj(w);
	return (0);
}
