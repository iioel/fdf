/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:53:41 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/08 14:55:49 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	catch_exit(int t, t_window *w)
{
	w = save_window(NULL);
	mlx_destroy_window(w->mlx, w->w);
	exit(0);
}

