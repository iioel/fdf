#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fdf.h"

int catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	mlx_destroy_window(w->cn, w->w);
	exit(0);
	return (0);
}

void	set_hsv(short hsv_c[3], int H, double S, double V)
{
	hsv_c[0] = H;
	hsv_c[1] = S;
	hsv_c[2] = V;
}

void	set_rgb_d(double hsv_c[3], double H, double S, double V)
{
	hsv_c[0] = H;
	hsv_c[1] = S;
	hsv_c[2] = V;
}

t_pixel get_pixel(t_window *w, int x, int y, int z)
{
	t_pixel	d;
	int		x_e;
	int		y_e;

	x_e = w->tile_width / 2;
	y_e = (w->col) * w->tile_height / 2;
	while (x-- > 0)
	{
		x_e += w->tile_width / 2;
		y_e -= w->tile_height / 2;
	}
	while (y-- > 0)
	{
		x_e += w->tile_width / 2;
		y_e += w->tile_height / 2;
	}
	y_e -= z * w->tile_height * 0.15;
	d.x = x_e;
	d.y = y_e;
	set_hsv(d.hsv_c, 60 + z * 26, z * 10, 75);
	return (d);
}

int hsv2rgb(short H, short S, short V)
{
	double			C;
	double			X;
	double			m;
	double			SV[2];
	double			rgb[3];

	SV[0] = S / 100.0;
	SV[1] = V / 100.0;
	C = SV[1] * SV[0];
	X = C * (1 - abs((H / 60) % 2 - 1));
	m = SV[1] - C;

	if (0 <= H && H <= 60)
		set_rgb_d(rgb, C, X, 0);
	else if (60 <= H && H <= 120)
		set_rgb_d(rgb, X, C, 0);
	else if (120 <= H && H <= 180)
		set_rgb_d(rgb, 0, C, X);
	else if (180 <= H && H <= 240)
		set_rgb_d(rgb, 0, X, C);
	else if (240 <= H && H <= 300)
		set_rgb_d(rgb, X, 0, C);
	else if (300 <= H && H <= 360)
		set_rgb_d(rgb, C, 0, X);

	return ((int)((rgb[0] + m) * 255) * 0x10000 + (int)((rgb[1] + m) * 255) * 0x100 + (int)((rgb[2] + m) * 255));
}

void line_put(t_window *w, t_pixel a, t_pixel b)
{
	double x;
	double y;
	double m;
	double m_c[3];
	short hsv_c[3];

	x = 0.;
	y = 0.;
	m = (b.y - a.y) / (double)(b.x - a.x);
	m_c[0] = (b.hsv_c[0] - a.hsv_c[0]) / (double)(b.x - a.x);
	m_c[1] = (b.hsv_c[1] - a.hsv_c[1]) / (double)(b.x - a.x);
	m_c[2] = (b.hsv_c[2] - a.hsv_c[2]) / (double)(b.x - a.x);
	while ((int)x < (a.x - b.x))
	{
		y = m * x;
		hsv_c[0] = b.hsv_c[0] + (short)(m_c[0] * x);
		hsv_c[1] = b.hsv_c[1] + (short)(m_c[1] * x);
		hsv_c[2] = b.hsv_c[2] + (short)(m_c[2] * x);
		printf("%d + %f, %d + %f, %d + %f = %x\n", hsv_c[0], m_c[0], hsv_c[1], m_c[1], hsv_c[2], m_c[2], hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		if ((int)(y) - (int)(m * (x + 1)) < 0)
			while ((int)(y) - (int)(m * (x + 1)) <= 0)
				mlx_pixel_put(w->cn, w->w, (int)x + b.x, (int)y++ + b.y, hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		else
			while ((int)(y) - (int)(m * (x + 1)) >= 0)
				mlx_pixel_put(w->cn, w->w, (int)x + b.x, (int)y-- + b.y, hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		x++;
	}
}

int display(t_window *w)
{
	t_pixel	p;
	int		x;
	int		y;

	int 	t[4 * 4] = {0,0,0,0,0,5,6,0,0,7,8,0,0,0,0,0};

	x = 0;
	y = 0;
	mlx_clear_window(w->cn, w->w);
	while (x < w->col)
	{
		y = 0;
		while (y < w->col)
		{
			p = get_pixel(w, x, y, t[x + y * w->col]);
			mlx_pixel_put(w->cn, w->w, p.x, p.y, hsv2rgb(p.hsv_c[0], p.hsv_c[1], p.hsv_c[2]));
			if (x != 0)
				line_put(w, p, get_pixel(w, x - 1, y, t[x - 1 + y * w->col]));
			if (y != 0)
				line_put(w, p, get_pixel(w, x, y - 1, t[x + (y - 1)* w->col]));
			y++;
		}
		x++;
	}
	return (0);
}


int main (void)
{
	t_window *w;

	w = malloc(sizeof(t_window));
	w->width = 600;
	w->height = 600;
	w->cn = mlx_init();
	w->w = mlx_new_window(w->cn, w->width, w->height, "test");
	w->tile_width = 128;
	w->tile_height = 96;
	w->col = 4;
	
	display(w);

	mlx_key_hook(w->w, catch_key, w);
	mlx_loop(w->cn);
}
