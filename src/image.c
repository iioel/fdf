/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:59:05 by ycornamu          #+#    #+#             */
/*   Updated: 2021/12/14 16:30:29 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*create_image(t_window *w)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (! img)
		return (NULL);
	img->width = w->width;
	img->height = w->height;
	img->img = mlx_new_image(w->mlx, img->width, img->height);
	if (! img->img)
	{
		free(img);
		return (NULL);
	}
	img->pixel_bits = 4 * 8;
	img->line_bytes = 4 * w->width;
	img->endian = 0;
	img->addr = mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->line_bytes, &img->endian);
	return (img);
}
