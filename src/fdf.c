/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:14:05 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 14:45:18 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"

t_window	*save_window(t_window *w)
{
	static t_window	*win = NULL;

	if (w != NULL)
		win = w;
	return (win);
}

int	error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

int	main(int ac, char **av)
{
	t_window	*w;
	t_obj		*obj;

	if (ac == 2)
	{
		obj = create_obj(av[1]);
		if (! obj)
			exit(1);
		w = create_win(2000, 1200, "fdf");
		if (! w)
			exit(clean_obj(obj, NULL));
		w->obj = obj;
		save_window(w);
		w->scale = (w->width - w->width * 0.3) / w->obj->width;
		w->obj->distance *= w->scale * w->obj->width * 7;
		render_obj(w);
		display_obj(w);
		mlx_hook(w->w, 2, (1L << 0), catch_key, w);
		mlx_hook(w->w, 17, (1L << 0), catch_exit, w);
		mlx_hook(w->w, 4, (1L << 2), catch_button_press, w);
		mlx_hook(w->w, 5, (1L << 3), catch_button_release, w);
		mlx_hook(w->w, 6, (1L << 8), catch_mouse_moves, w);
		mlx_hook(w->w, 6, (1L << 6), catch_mouse_moves, w);
		mlx_do_key_autorepeaton(w->mlx);
		mlx_loop(w->mlx);
	}
}
