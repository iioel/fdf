/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:21:22 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/12 16:13:26 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hsv(short hsv_c[3], int H, double S, double V)
{
	hsv_c[0] = H;
	hsv_c[1] = S;
	hsv_c[2] = V;
}

void	set_hsv_d(double hsv_c[3], double H, double S, double V)
{
	hsv_c[0] = H;
	hsv_c[1] = S;
	hsv_c[2] = V;
}

void	conv_rgb(double rgb[3], short h, double c, double x)
{
	if (0 <= h && h <= 60)
		set_hsv_d(rgb, c, x, 0);
	else if (60 <= h && h <= 120)
		set_hsv_d(rgb, x, c, 0);
	else if (120 <= h && h <= 180)
		set_hsv_d(rgb, 0, c, x);
	else if (180 <= h && h <= 240)
		set_hsv_d(rgb, 0, x, c);
	else if (240 <= h && h <= 300)
		set_hsv_d(rgb, x, 0, c);
	else if (300 <= h && h <= 360)
		set_hsv_d(rgb, c, 0, x);
}

int	hsv2rgb(short h, short s, short v)
{
	double			c;
	double			x;
	double			m;
	double			sv[2];
	double			rgb[3];

	sv[0] = s / 100.0;
	sv[1] = v / 100.0;
	while (h < 0 || h > 360)
	{
		if (h < 0)
			h *= -1;
		else
			h /= 360;
	}
	c = sv[1] * sv[0];
	x = c * (1 - ft_abs((h / 60) % 2 - 1));
	m = sv[1] - c;
	conv_rgb(rgb, h, c, x);
	return (((int)((rgb[0] + m) * 255) << (2 * 8))
			+ ((int)((rgb[1] + m) * 255) << (1 * 8))
			+ (int)((rgb[2] + m) * 255));
}
