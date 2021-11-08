/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:14:10 by yoel              #+#    #+#             */
/*   Updated: 2021/11/08 18:26:21 by yoel             ###   ########.fr       */
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

static int	read_line(char *line, short **tab, int *tab_i, t_window *w)
{
	int j;
	int nb_word;
	short *temp;

	nb_word = ft_strcntword(line, ' ');
	temp = malloc((*tab_i + nb_word) * sizeof(short));
	if (!temp)
		return (1);
	j = -1;
	while (++j < *tab_i)
		temp[j] = (*tab)[j];
	free(*tab);
	*tab = temp;
	j += nb_word;
	while (*tab_i < j)
	{
		(*tab)[*tab_i] = ft_atoinskip(&line);
		if ((*tab)[(*tab_i)++] > w->grid_h)
			w->grid_h = (*tab)[*tab_i - 1];
	}
	if (! w->grid_w)
	{
		w->grid_w = nb_word;
		w->scale = (w->width - w->width * 0.3) / w->grid_w;
	}
	w->grid_l = *tab_i / w->grid_w;	
	return (0);
}

short *read_file(char *f, t_window *w)
{
	int fd;
	int i;
	char *line;
	short *tab;

	i = 0;
	w->grid_h = 0;
	fd = open(f, O_RDONLY);
	tab = NULL;

	line = get_next_line(fd);
	while (line)
	{
		if (read_line(line, &tab, &i, w))
			return (NULL);
		free(line);
		line = get_next_line(fd);
		w->t = tab;
		//display(w);
	}
	free(line);
	return (tab);
}
