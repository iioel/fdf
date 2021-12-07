/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:14:05 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/08 00:24:25 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"

t_window *save_window(t_window *w)
{
	static t_window *win = NULL;

	if (w != NULL)
		win = w;
	return (win);
}

int	catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	if (t == 53 || t == 65307) // ESC
	{
		mlx_destroy_window(w->mlx, w->w);
		exit(0);
	}
	else if (t == 8) // c
		mlx_clear_window(w->mlx, w->w);
	else if (t == 126 || t == 65362) // UP
		w->scale *= 1.05;
	else if (t == 125 || t == 65364) // DOWN
		w->scale *= (1 / 1.05);
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
	update_mtx(w->obj);
	render_obj(w);
	display_obj(w);
	return (0);
}

int	catch_button_press(int t, t_window *w)
{
	w = save_window(NULL);
	printf("pressed button : %d\n", t);
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
	printf("released button : %d\n", t);
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
		printf("move: %d x %d\n", x, y);
		render_obj(w);
		display_obj(w);
	}
	else if (x_from != -1)
	{
		x_from = -1;
		y_from = -1;
		org_off_x = 0;
		org_off_y = 0;
		printf("move: reseted\n");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_window	*w;

	if (ac == 2)
	{
		w = create_win(2000, 1200, "fdf");
		save_window(w);
		w->obj = create_obj(av[1]);
		w->scale = (w->width - w->width * 0.3) / w->obj->width;
		render_obj(w);
		display_obj(w);
		mlx_hook(w->w, 2, (1L << 0), catch_key, w);
		mlx_hook(w->w, 4, (1L << 2), catch_button_press, w);
		mlx_hook(w->w, 5, (1L << 3), catch_button_release, w);
		mlx_hook(w->w, 6, (1L << 8), catch_mouse_moves, w);
		mlx_hook(w->w, 6, (1L << 6), catch_mouse_moves, w);
		mlx_do_key_autorepeaton(w->mlx);
		mlx_loop(w->mlx);
	}
}
