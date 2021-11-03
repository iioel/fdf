/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:07:33 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/03 15:08:12 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_window
{
	void	*cn;
	void	*w;
	int		width;
	int		height;
	int		a;
	int		b;
	int		c;
	int		grid_w;
	int 	grid_l;
	int 	grid_h;
	int 	scale;
	int		tile_rot;
	int		tile_width;
	int		tile_height;
	short	*t;
}				t_window;

typedef struct s_pixel
{
	int x;
	int y;
	short hsv_c[3];
}				t_pixel;

int display(t_window *w);

#endif
