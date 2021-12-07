/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:42:59 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/07 23:42:29 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window	*create_win(int x, int y, char *name)
{
	t_window	*w;

	w = ft_calloc(1, sizeof(t_window));
	w->img = NULL;
	w->obj = NULL;
	w->scale = 1;
	w->offx = 0;
	w->offy = 0;
	w->moving = 0;
	w->width = x;
	w->height = y;
	w->mlx = mlx_init();
	w->w = mlx_new_window(w->mlx, x, y, name);
	return (w);
}
