/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:14:10 by yoel              #+#    #+#             */
/*   Updated: 2021/12/14 16:13:15 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

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

static int	extend_grid(short **grid, int len, int nb_word)
{
	int		j;
	short	*temp;

	temp = malloc((len + nb_word) * sizeof(short));
	if (!temp)
	{
		free(*grid);
		*grid = NULL;
		return (error(strerror(errno)));
	}
	j = -1;
	while (++j < len)
		temp[j] = (*grid)[j];
	free(*grid);
	*grid = temp;
	return (0);
}

static int	read_line(char *line, short **grid, int *grid_len, t_obj *obj)
{
	int		j;
	int		nb_word;

	nb_word = ft_strcntword(line, ' ');
	if (extend_grid(grid, *grid_len, nb_word))
	{
		free(line);
		return (1);
	}
	j = *grid_len + nb_word;
	while (*grid_len < j)
	{
		(*grid)[*grid_len] = ft_atoinskip(&line);
		if ((*grid)[(*grid_len)++] > obj->height)
			obj->height = (*grid)[*grid_len - 1];
	}
	if (! obj->width)
		obj->width = nb_word;
	if (nb_word < obj->width)
		return (error("Found wrong line length ! Exiting..."));
	obj->length = *grid_len / obj->width;
	return (0);
}

int	read_file(char *f, t_obj *obj)
{
	int		fd;
	int		grid_len;
	char	err;
	char	*line;
	short	*grid;

	err = 0;
	grid_len = 0;
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (error(strerror(errno)));
	grid = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (read_line(line, &grid, &grid_len, obj))
			err = 1;
		free(line);
		line = get_next_line(fd);
		obj->grid = grid;
	}
	if (err)
		return (1);
	return (0);
}
