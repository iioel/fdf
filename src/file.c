/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:14:10 by yoel              #+#    #+#             */
/*   Updated: 2021/11/12 16:31:47 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"

static size_t	ft_strcntword(char const *s, char sep)
{
	size_t	i;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	while (*(s + i) != 0)
	{
		while (*(s + i) == sep && *(s + i))
			i++;
		if (*s + i)
		{
			while (*(s + i) != sep && *(s + i))
				i++;
			nb_words++;
		}
	}
	return (nb_words);
}

static int	ft_atoinskip(char **str)
{
	size_t	i;
	int		factor;
	int		res;

	i = 0;
	factor = 1;
	res = 0;
	while ((**str == '\t' || **str == '\n' || **str == '\v'
			|| **str == '\f' || **str == '\r' || **str == ' ') && **str)
		(*str)++;
	if (**str == '+' || **str == '-')
		if (*((*str)++) == '-')
			factor = -1;
	while (ft_isdigit(**str) && **str)
	{
		res *= 10;
		res += *((*str)++) - '0';
	}
	while (**str != ' ' && **str)
		(*str)++;
	return (res * factor);
}

static int	read_line(char *line, short **grid, int *grid_len, t_obj *obj)
{
	int		j;
	int		nb_word;
	short	*temp;

	nb_word = ft_strcntword(line, ' ');
	temp = malloc((*grid_len + nb_word) * sizeof(short));
	if (!temp)
		return (1);
	j = -1;
	while (++j < *grid_len)
		temp[j] = (*grid)[j];
	free(*grid);
	*grid = temp;
	j += nb_word;
	while (*grid_len < j)
	{
		(*grid)[*grid_len] = ft_atoinskip(&line);
		if ((*grid)[(*grid_len)++] > obj->height)
			obj->height = (*grid)[*grid_len - 1];
	}
	if (! obj->width)
		obj->width = nb_word;
	//w->scale = (w->width - w->width * 0.3) / w->grid_w;
	obj->length = *grid_len / obj->width;
	return (0);
}

int	read_file(char *f, t_obj *obj)
{
	int		fd;
	int		grid_len;
	char	*line;
	short	*grid;

	grid_len = 0;
	fd = open(f, O_RDONLY);
	grid = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (read_line(line, &grid, &grid_len, obj))
			return (1);
		free(line);
		line = get_next_line(fd);
		obj->grid = grid;
	}
	free(line);
	return (0);
}
