/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:07:33 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/08 03:04:28 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_img
{
	void *img;
	char *addr;
	int		width;
	int		height;
	int pixel_bits;
	int line_bytes;
	int endian;
}				t_img;

typedef struct s_window
{
	void	*cn;
	void	*w;
	t_img	*img;
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
	double	(*rotX)[3][3];
	double	(*rotY)[3][3];
	double	(*rotZ)[3][3];
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
