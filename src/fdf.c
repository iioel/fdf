#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"

void mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color);

int catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	if (t == 53 || t == 65307) // ESC
	{
		mlx_destroy_window(w->mlx, w->w);
		exit(0);
	}
	else if (t == 8) // c
		mlx_clear_window(w->mlx, w->w);
	else if (t == 15 || t == 114)
		display(w);
	else if (t == 126 || t == 65362) // UP
		w->scale++;
	else if (t == 125 || t == 65364) // DOWN
		w->scale--;
	else if (t == 13 || t == 119) // w
		w->alpha += 2;
	else if (t == 0 || t == 97) // a
		w->beta -= 2;
	else if (t == 1 || t == 115) // s
		w->alpha -= 2;
	else if (t == 2 || t == 100) // d
		w->beta += 2;
	else if (t == 12 || t == 113) // q
		w->gamma -= 2;
	else if (t == 14 || t == 101) // e
		w->gamma += 2;
	else if (t == 7 || t == 120) // x
		w->alpha = 0;
	else if (t == 16 || t == 121) // y
		w->beta = 0;
	else if (t == 6 || t == 122) // z
		w->gamma = 0;
	display(w);

	return (0);
}

void	mtx_mul(double a[3][3], double b[3][1], double res[3][1])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 1)
		{
			k = 0;
			res[i][j] = 0;
			while (k < 3)
			{
				res[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

t_pixel	get_pixel(t_window *w, int x, int y, int z)
{
	t_pixel	d;
	double	x_e;
	double	y_e;
	double	point[3][1];
	double	res[3][1] = {{0},{0},{0}};

	point[0][0] = ((double)x - w->grid_w / 2) * w->scale;
	point[1][0] = ((double)y - w->grid_l / 2) * w->scale;
	point[2][0] = ((double)z - w->grid_h / 2) * w->scale;
	mtx_mul(*(w->rotX), point, res);
	mtx_mul(*(w->rotY), res, point);
	mtx_mul(*(w->rotZ), point, res);
	d.x = (int)res[0][0] + w->width / 2;
	d.y = (int)res[1][0] + w->height / 2;
	set_hsv(d.hsv_c, 60 + z * 26, 40, 100);
	//set_hsv(d.hsv_c, 60, 0, 100);
	return (d);
}

void	line_put(t_window *w, t_pixel a, t_pixel b)
{
    int		steps, i;
	double	x, y, x_i, y_i, hsv_c[3];
	double	hsv_i[3];
    x = a.x;
    y = a.y;
	set_hsv_d(hsv_c, a.hsv_c[0], a.hsv_c[1], a.hsv_c[2]);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		steps = abs(b.x - a.x);
	else
		steps = abs(b.y - a.y);
	x_i = (b.x - a.x) / (double)steps;
	y_i = (b.y - a.y) / (double)steps;
	set_hsv_d(hsv_i, (b.hsv_c[0] - a.hsv_c[0]) / (double)steps, (b.hsv_c[1] - a.hsv_c[1]) / (double)steps, (b.hsv_c[2] - a.hsv_c[2]) / (double)steps);
	i = 0;
	while (i < steps)
	{
		x += x_i;
		y += y_i;
		hsv_c[0] += hsv_i[0];
		hsv_c[1] += hsv_i[1];
		hsv_c[2] += hsv_i[2];
		mlx_pixel_put_img(w->img, (int)x, (int)y, hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		i++;
	}
}

void	mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color)
{
	char	*p_loc;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		p_loc = img->addr + (y * img->line_bytes + x * (img->pixel_bits / 8));
		*(unsigned int *)p_loc = color;
	}
}

int	display(t_window *w)
{
	t_pixel	p;
	t_img	img;
	int		x;
	int		y;
	short	*t;
	double	a = w->alpha * M_PI / 180;
	double	b = w->beta * M_PI / 180;
	double	c = w->gamma * M_PI / 180;

	t = w->t;

	x = 0;
	y = 0;
	img.width = w->width;
	img.height = w->height;
	img.img = mlx_new_image(w->mlx, img.width, img.height);
	img.pixel_bits = 4 * 8;
	img.line_bytes = 4 * w->width;
	img.endian = 0;
	img.addr = mlx_get_data_addr(img.img, &img.pixel_bits, &img.line_bytes, &img.endian);
	w->img = &img;
	double rotX[3][3] = {{		1,		 0, 	  0},
						 {		0,	cos(a),	-sin(a)},
						 {		0,	sin(a),	 cos(a)}};
	double rotY[3][3] = {{ cos(b),		 0,  sin(b)},
						 {		0,		 1, 	  0},
						 {-sin(b),		 0,  cos(b)}};
	double rotZ[3][3] = {{ cos(c), -sin(c),		  0},
						 { sin(c),	cos(c),		  0},
						 {		0,		 0,		  1}};
	w->rotX = &rotX;
	w->rotY = &rotY;
	w->rotZ = &rotZ;
	while (x < w->grid_w)
	{
		y = 0;
		while (y < w->grid_l)
		{
			p = get_pixel(w, x, y, t[x + y * w->grid_w]);
			mlx_pixel_put_img(w->img, p.x, p.y, hsv2rgb(p.hsv_c[0], p.hsv_c[1], p.hsv_c[2]));
			if (x != 0)
				line_put(w, p, get_pixel(w, x - 1, y, t[x - 1 + y * w->grid_w]));
			if (y != 0)
				line_put(w, p, get_pixel(w, x, y - 1, t[x + (y - 1)* w->grid_w]));
			y++;
		}
		x++;
	}
	mlx_clear_window(w->mlx, w->w);
	mlx_put_image_to_window(w->mlx, w->w, img.img, 0, 0);
	mlx_destroy_image(w->mlx, img.img);
	return (0);
}

int main (int ac, char **av)
{
	t_window	*w;

	if (ac == 2)
	{
		w = malloc(sizeof(t_window));
		w->width = 1000;
		w->height = 600;
		w->mlx = mlx_init();
		w->w = mlx_new_window(w->mlx, w->width, w->height, "test");
		w->alpha = 35;
		w->beta = 45;
		w->gamma = 0;
		w->grid_w = 0;
		w->grid_w = 0;
		w->t = read_file(av[1], w);
		
		display(w);

		//mlx_key_hook(w->w, catch_key, w);
		mlx_hook(w->w, 2, (1L<<0), catch_key, w);
		mlx_do_key_autorepeaton(w->mlx);
		mlx_loop(w->mlx);
	}
}
