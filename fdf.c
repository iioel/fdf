#include "mlx.h"
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
	if (t == 65307)
		mlx_destroy_window(w->cn, w->w);
}

void get_dot_coords(t_window *w, t_dot d)
{
	int x_e;
	int y_e;

	x_e = w->tile_width / 2;
	y_e = (w->col) * w->tile_height / 2;
	while (d.x-- > 0)
	{
		x_e += w->tile_width / 2;
		y_e -= w->tile_height / 2;
	}
	while (d.y-- > 0)
	{
		x_e += w->tile_width / 2;
		y_e += w->tile_height / 2;
	}
	mlx_pixel_put(w->cn, w->w, x_e, y_e, d.color);
}

int display(t_window *w)
{
	t_dot d0 = {.x = 0, .y = 0, .color = 0x00FF0000};
	t_dot d1 = {.x = 1, .y = 0, .color = 0x00FF0000};

	mlx_clear_window(w->cn, w->w);
	place_dot(w, d0);
	//d = {0, 1, 0x00FF0000};
	place_dot(w, d1);
	//place_dot(w, 1, 0, 0x00FFFFFF);
	//place_dot(w, 1, 1, 0x00FFFFFF);
}


int main (void)
{
	t_window *w;

	w = malloc(sizeof(t_window));
	w->width = 800;
	w->width = 600;
	w->cn = mlx_init();
	w->w = mlx_new_window(w->cn, 600, 600, "test");
	w->tile_width = 128;
	w->tile_height = 64;
	w->col = 2;
	
	display(w);

	mlx_key_hook(w->w, catch_key, w);
	mlx_loop(w->cn);
}
