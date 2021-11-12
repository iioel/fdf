/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:07:33 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/12 13:05:39 by ycornamu         ###   ########.fr       */
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
	void	*mlx;
	void	*w;
	t_img	*img;
	int		width;
	int		height;
	int		alpha;
	int		beta;
	int		gamma;
	int		grid_w;
	int 	grid_l;
	int 	grid_h;
	int 	scale;
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


int		display(t_window *w);

// file.c
short 	*read_file(char *f, t_window *w);

// color.c
void	set_hsv(short hsv_c[3], int H, double S, double V);
void	set_hsv_d(double hsv_c[3], double H, double S, double V);
void	conv_rgb(double rgb[3], short h, double c, double x);
int		hsv2rgb(short h, short s, short v);

// math.c
int		ft_abs(int i);

#endif
