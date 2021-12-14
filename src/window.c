/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:42:59 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 14:21:52 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	*clean(void *pointer)
{
	free(pointer);
	return (NULL);
}

t_window	*create_win(int x, int y, char *name)
{
	t_window	*w;

	w = ft_calloc(1, sizeof(t_window));
	if (! w)
		return (NULL);
	w->obj = NULL;
	w->scale = 1;
	w->offx = 0;
	w->offy = 0;
	w->moving = 0;
	w->width = x;
	w->height = y;
	w->mlx = mlx_init();
	if (! w->mlx)
		return (clean(w));
	w->w = mlx_new_window(w->mlx, x, y, name);
	if (! w->w)
		return (clean(w));
	return (w);
}

int	clean_win(t_window *w)
{	
	mlx_destroy_window(w->mlx, w->w);
	if (w->obj)
		clean_obj(w->obj, w->mlx);
	free(w);
	return (0);
}
