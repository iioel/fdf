#include "minilibx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_window
{
	void	*cn;
	void	*w;
	int		width;
	int		height;
	int		tile_width;
	int		tile_height;
	int		col;
}				t_window;

typedef struct s_dot
{
	int x;
	int y;
	int color;
}				t_dot;

int display(t_window *w);

int catch_key(int t, t_window *w)
{
	printf("key : %d\n", t);
	mlx_destroy_window(w->cn, w->w);
	return (0);
}

t_dot get_dot(t_window *w, int x, int y, int z)
{
	t_dot	d;
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
	y_e -= z * w->tile_height * 0.8;
	d.x = x_e;
	d.y = y_e;
	d.color = 0x00FFFFFF;
	return (d);
}

void line_put(t_window *w, t_dot a, t_dot b)
{
	double x;
	double y;
	double m;

	x = 0.;
	y = 0.;
	m = (b.y - a.y) / (double)(b.x - a.x);
//	if (a.x > b.x)
//		sign = -1;
	while ((int)x < (a.x - b.x))
	{
		y = m * x;
		mlx_pixel_put(w->cn, w->w, (int)x + b.x, (int)y + b.y, 0x00FFFFFF);
		x++;
	}
}

int display(t_window *w)
{
	t_dot	d;
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx_clear_window(w->cn, w->w);
	while (x < w->col)
	{
		y = 0;
		while (y < w->col)
		{
			d = get_dot(w, x, y, 0);
			mlx_pixel_put(w->cn, w->w, d.x, d.y, d.color);
			if (x != 0)
				line_put(w, d, get_dot(w, x - 1, y, 0));
			if (y != 0)
				line_put(w, d, get_dot(w, x, y - 1, 0));
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
