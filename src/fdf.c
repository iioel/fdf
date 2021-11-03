#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"

int catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	if (t == 53 || t == 65307)
	{
		mlx_destroy_window(w->cn, w->w);
		exit(0);
	}
	else if (t == 8)
		mlx_clear_window(w->cn, w->w);
	else if (t == 15 || t == 114)
		display(w);
	else if (t == 126 || t == 65362)
		w->scale++;
	else if (t == 125 || t == 65364)
		w->scale--;
	else if (t == 123 || t == 65361)
		w->tile_rot++;
	else if (t == 124 || t == 65363)
		w->tile_rot--;
	else if (t == 13) // w
		w->a++;
	else if (t == 0) // a
		w->b--;
	else if (t == 1) // s
		w->a--;
	else if (t == 2) // d
		w->b++;
	else if (t == 12) // q
		w->c--;
	else if (t == 14) // e
		w->c++;
	display(w);

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

void mtx_mul(double a[3][3], double b[3][1], double res[3][1])
{
	int i, j, k;

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
				//printf("%f += %f * %f\n", res[i][j], a[i][k], b[k][j]);
				res[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

t_pixel get_pixel(t_window *w, int x, int y, int z)
{
	t_pixel	d;
	double		x_e;
	double		y_e;
	double a = w->a * M_PI / 180;
	double b = w->b * M_PI / 180;
	double c = w->c * M_PI / 180;
	double point[3][1] = {{(double)x},
					{(double)y},
					{(double)z}};
	double rotX[3][3] = {{1, 		0, 		  0},
					   {0, cos(a),	-sin(a)},
					   {0, sin(a),	 cos(a)}};
	double rotY[3][3] = {{cos(b), 0, sin(b)},
					   {0, 		1, 		0},
					   {-sin(b), 0, cos(b)}};
	double rotZ[3][3] = {{cos(c), -sin(c), 0},
					   {sin(c),	cos(c), 0},
					   {0,		0,		1}};
	double msq[3][3] = {{1, 0, 0},
					  {0, 1, 0},
					  {0, 0, 0}};
	double res[3][1] = {{0},{0},{0}};
	
	mtx_mul(rotX, point, res);
	mtx_mul(rotY, res, point);
	mtx_mul(rotZ, point, res);
	mtx_mul(msq, res, point);
	d.x = (int)point[0][0] * w->scale;
	d.y = (int)point[1][0] * w->scale;
	printf("%dx%d : x%d y%d z%d\n", x, y, (int)point[0][0], (int)point[1][0], (int)point[2][0]);
	set_hsv(d.hsv_c, 60 + z * 26, 40, 50);//abs(z * 10), 75);
	//set_hsv(d.hsv_c, 60, 0, 100);
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
	while (H < 0 || H > 360)
		if (H < 0)
			H *= -1;
		else
			H /= 360;
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
		//printf("%d + %f, %d + %f, %d + %f = %x\n", hsv_c[0], m_c[0], hsv_c[1], m_c[1], hsv_c[2], m_c[2], hsv2rgb(hsv_c[0], hsv_c[1], hsv_c[2]));
		if ((int)(y) - (int)(m * (x + 1)) <= 0)
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
	short *t;

	t = w->t;
	//int 	t[4 * 4] = {0,0,0,0,0,5,6,0,0,7,8,0,0,0,0,0};

	x = 0;
	y = 0;
	w->tile_height = w->tile_width / 1.6;
	mlx_clear_window(w->cn, w->w);
	while (x < w->grid_w)
	{
		y = 0;
		while (y < w->grid_l)
		{
			p = get_pixel(w, x, y, t[x + y * w->grid_w]);
			mlx_pixel_put(w->cn, w->w, p.x, p.y, hsv2rgb(p.hsv_c[0], p.hsv_c[1], p.hsv_c[2]));
		//	if (x != 0)
		//		line_put(w, p, get_pixel(w, x - 1, y, t[x - 1 + y * w->grid_w]));
			if (y != 0)
				line_put(w, p, get_pixel(w, x, y - 1, t[x + (y - 1)* w->grid_w]));
			y++;
		}
		x++;
	}
	return (0);
}

short *read_file(char *f, t_window *w)
{
	int fd;
	int i;
	int j;
	char *line;
	char **t_line;
	short *tab;
	short *temp;


	i = 0;
	w->grid_h = 0;
	fd = open(f, O_RDONLY);
	tab = NULL;

	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		t_line = ft_split(line, ' ');
		if (! t_line)
			exit(1);
		while (t_line[j])
			j++;
		temp = malloc((i + j) * sizeof(short));
		if (!temp)
			return (NULL);
		j = -1;
		while (++j < i)
			temp[j] = tab[j];
		free(tab);
		tab = temp;
		j = 0;
		while (t_line[j])
		{
			tab[i] = ft_atoi(t_line[j]);
			if (tab[i++] > w->grid_h)
				w->grid_h = tab[i - 1];
			free(t_line[j++]);
		}
		free(t_line);
		free(line);
		line = get_next_line(fd);
		w->grid_w = j;
		w->grid_l = i / (j);
		//w->tile_width = 128 / (w->grid_w / 4);
		w->tile_width = 7;
		w->tile_height = w->tile_width / 1.7;
		
		//display(w, tab);
	}
	w->tile_rot = 0;
	return (tab);
}


int main (int ac, char **av)
{
	t_window *w;
	//short *t;

	if (ac == 2)
	{
		w = malloc(sizeof(t_window));
		w->width = 800;
		w->height = 600;
		w->cn = mlx_init();
		w->w = mlx_new_window(w->cn, w->width, w->height, "test");
		w->t = read_file(av[1], w);
		w->a = 0;
		w->b = 0;
		w->c = 0;
		w->scale = 10;
		//w->tile_width = 128 / (w->grid_w / 4);
		//w->tile_height = 60 / (w->grid_h / 4);
		
		display(w);

		//mlx_loop_hook(w->w, display, w);
		mlx_key_hook(w->w, catch_key, w);
		mlx_loop(w->cn);
	}
}
