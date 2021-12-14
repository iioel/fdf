/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:07:33 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 12:43:16 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_W 13
# define KEY_A 0 
# define KEY_S 1 
# define KEY_D 2 
# define KEY_Q 12
# define KEY_E 14
# define KEY_X 7 
# define KEY_Y 16
# define KEY_Z 6 
# define KEY_I 34
# define KEY_P 35

# define KEY_ESC_LINUX 65307
# define KEY_UP_LINUX 65362
# define KEY_DOWN_LINUX 65364
# define KEY_W_LINUX 119
# define KEY_A_LINUX 97
# define KEY_S_LINUX 115
# define KEY_D_LINUX 100
# define KEY_Q_LINUX 113
# define KEY_E_LINUX 101
# define KEY_X_LINUX 120
# define KEY_Y_LINUX 121
# define KEY_Z_LINUX 122
# define KEY_I_LINUX 105
# define KEY_P_LINUX 112

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
}				t_img;

typedef struct s_obj
{
	int		height;
	int		width;
	int		length;
	int		anglx;
	int		angly;
	int		anglz;
	double	rotx[3][3];
	double	roty[3][3];
	double	rotz[3][3];
	short	*grid;
	int		projected;
	double	distance;
	t_img	*img;
}				t_obj;

typedef struct s_window
{
	void	*mlx;
	void	*w;
	int		width;
	int		height;
	t_obj	*obj;
	int		offx;
	int		offy;
	int		moving;
	double	scale;
}				t_window;

typedef struct s_pixel
{
	int		x;
	int		y;
	short	hsv_c[3];
}				t_pixel;

typedef struct s_line
{
	int		steps;
	double	x;
	double	y;
	double	x_i;
	double	y_i;
	double	hsv_c[3];
	double	hsv_c_i[3];
}				t_line;

t_window	*save_window(t_window *w);

// file.c
int			read_file(char *f, t_obj *obj);

// color.c
void		set_hsv(short hsv_c[3], int H, double S, double V);
void		set_hsv_d(double hsv_c[3], double H, double S, double V);
void		conv_rgb(double rgb[3], short h, double c, double x);
int			hsv2rgb(short h, short s, short v);

// catch_win.c
int			catch_exit(int t, t_window *w);

// catch_key.c
int			catch_key(int t, t_window *w);

// catch_mouse.c
int			catch_button_press(int t, t_window *w);
int			catch_button_release(int t, t_window *w);
int			catch_mouse_moves(int x, int y, t_window *w);

// math.c
int			ft_abs(int i);

// image.c
t_img		*create_image(t_window *w);

// mlx_utils.c
void		mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color);
void		rotate(double *x, double *y, double *z, t_window *w);
t_pixel		get_pixel(t_window *w, int x, int y, int z);

// line.c
t_line		*create_line(t_pixel a, t_pixel b);
void		line_put(t_window *w, t_pixel a, t_pixel b);

// mtx.c
void		mtx_mul(double a[3][3], double b[3][1]);
void		mtx_setline(double line[3][3], double a, double b, double c);

// obj.c
t_obj		*create_obj(char *file);
void		update_mtx(t_obj *obj);
void		add_angles(int alpha, int beta, int gamma, t_obj *obj);
void		display_obj(t_window *w);
void		clean_obj(t_obj *obj);

// obj_ext.c
void		render_obj(t_window *w);

// window.c
t_window	*create_win(int x, int y, char *name);
int			clean_win(t_window *w);

#endif
