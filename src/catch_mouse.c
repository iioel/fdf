/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:22 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/08 15:01:00 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	catch_button_press(int t, t_window *w)
{
	w = save_window(NULL);
//	printf("pressed button : %d\n", t);
	if (t == 5)
		w->scale *= 1.05;
	else if (t == 4)
		w->scale *= (1 / 1.05);
	else if (t == 1)
		w->moving = 1;
	update_mtx(w->obj);
	render_obj(w);
	display_obj(w);
	return (0);
}

int	catch_button_release(int t, t_window *w)
{
	w = save_window(NULL);
//	printf("released button : %d\n", t);
	if (t == 1)
		w->moving = 0;
	update_mtx(w->obj);
	render_obj(w);
	display_obj(w);
	return (0);
}

int	catch_mouse_moves(int x, int y, t_window *w)
{
	static int x_from = -1;
	static int y_from = -1;
	static int org_off_x = -1;
	static int org_off_y = -1;
	w = save_window(NULL);
	if (w->moving)
	{
		if (x_from == -1)
		{
			x_from = x;
			y_from = y;
			org_off_x = w->offx;
			org_off_y = w->offy;
		}
		w->offx = org_off_x + x - x_from;
		w->offy = org_off_y + y - y_from;
//		printf("move: %d x %d\n", x, y);
		render_obj(w);
		display_obj(w);
	}
	else if (x_from != -1)
	{
		x_from = -1;
		y_from = -1;
		org_off_x = 0;
		org_off_y = 0;
//		printf("move: reseted\n");
	}
	return (0);
}
