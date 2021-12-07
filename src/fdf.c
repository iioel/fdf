/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:14:05 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/07 20:14:25 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"

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
		w->scale++;
	else if (t == 125 || t == 65364) // DOWN
		w->scale--;
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

int	main(int ac, char **av)
{
	t_window	*w;

	if (ac == 2)
	{
		w = create_win(2000, 1200, "fdf");
		w->obj = create_obj(av[1]);
		w->scale = (w->width - w->width * 0.3) / w->obj->width;
		render_obj(w);
		display_obj(w);
		//mlx_key_hook(w->w, catch_key, w);
		mlx_hook(w->w, 2, (1L << 0), catch_key, w);
		mlx_do_key_autorepeaton(w->mlx);
		mlx_loop(w->mlx);
	}
}
