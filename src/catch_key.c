/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:53:10 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 12:51:09 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_projected(t_window *w)
{
	w->obj->projected = 1;
	w->scale = w->obj->distance / w->obj->width;
}

static void	set_isometric(t_window *w)
{
	w->obj->anglx = 45;
	w->obj->angly = 35;
	w->obj->anglz = -30;
	if (w->obj->projected)
	{
		w->obj->projected = 0;
		w->scale = (w->width - w->width * 0.3) / w->obj->width;
	}
}

static void	catch_key_ext(int t, t_window *w)
{
	if (t == KEY_X || t == KEY_X_LINUX)
		w->obj->anglx = 0;
	else if (t == KEY_Y || t == KEY_Y_LINUX)
		w->obj->angly = 0;
	else if (t == KEY_Z || t == KEY_Z_LINUX)
		w->obj->anglz = 0;
	else if (t == KEY_I || t == KEY_I_LINUX)
		set_isometric(w);
	else if (t == KEY_P || t == KEY_P_LINUX)
		set_projected(w);
}

int	catch_key(int t, t_window *w)
{
	w = save_window(NULL);
	if (t == KEY_ESC || t == KEY_ESC_LINUX)
		exit(clean_win(w));
	else if (t == KEY_UP || t == KEY_UP_LINUX)
		w->obj->distance *= (1 / 1.05);
	else if (t == KEY_DOWN || t == KEY_DOWN_LINUX)
		w->obj->distance *= 1.05;
	else if (t == KEY_W || t == KEY_W_LINUX)
		w->obj->anglx += 2;
	else if (t == KEY_A || t == KEY_A_LINUX)
		w->obj->angly -= 2;
	else if (t == KEY_S || t == KEY_S_LINUX)
		w->obj->anglx -= 2;
	else if (t == KEY_D || t == KEY_D_LINUX)
		w->obj->angly += 2;
	else if (t == KEY_Q || t == KEY_Q_LINUX)
		w->obj->anglz -= 2;
	else if (t == KEY_E || t == KEY_E_LINUX)
		w->obj->anglz += 2;
	else
		catch_key_ext(t, w);
	update_mtx(w->obj);
	render_obj(w);
	display_obj(w);
	return (0);
}
