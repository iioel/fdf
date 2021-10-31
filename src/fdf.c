#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_window
{
	void	*cn;
	void	*w;
	int		width;
	int		height;
	int		grid_w;
	int 	grid_h;
	int		tile_width;
	int		tile_height;
	int		col;
}				t_window;

typedef struct s_pixel
{
	int x;
	int y;
	int color;
}				t_pixel;

int display(t_window *w);

int catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	mlx_destroy_window(w->cn, w->w);
	return (0);
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
	y_e -= z * w->tile_height * 0.2;
	d.x = x_e;
	d.y = y_e;
	d.color = 0xFFFFFF;
	return (d);
}

void line_put(t_window *w, t_pixel a, t_pixel b)
{
	double x;
	double y;
	double m;

	x = 0.;
	y = 0.;
	m = (b.y - a.y) / (double)(b.x - a.x);
	while ((int)x < (a.x - b.x))
	{
		y = m * x;
		while (abs((int)(y) - (int)(m * (x + 1))))
		{
			mlx_pixel_put(w->cn, w->w, (int)x + b.x, (int)y + b.y, b.color);
			if ((int)(y) - (int)(m * (x + 1)) < 0)
				y++;
			else
				y--;
		}
		x++;
	}
}

int display(t_window *w)
{
	t_pixel	p;
	int		x;
	int		y;

	int 	t[4 * 4] = {0,0,0,0,0,10,10,0,0,10,10,0,0,0,0,0};

	x = 0;
	y = 0;
	mlx_clear_window(w->cn, w->w);
	while (x < w->col)
	{
		y = 0;
		while (y < w->col)
		{
			p = get_pixel(w, x, y, t[x + y * w->col]);
			mlx_pixel_put(w->cn, w->w, p.x, p.y, p.color);
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
	w->tile_height = 78;
	w->col = 4;
	
	display(w);

	mlx_key_hook(w->w, catch_key, w);
	mlx_loop(w->cn);
}
