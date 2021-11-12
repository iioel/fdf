/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/12 13:13:38 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

// In file get_next_line_utils.c
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE],
				const size_t s2_size);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// In this file
static int	read_line(int fd, char **readed);
static char	*return_line(char **readed);
static char	*clean(char **s);

char	*get_next_line(int fd)
{
	static char	*readed;
	size_t		nb_readed;

	if (read(fd, 0, 0))
		return (clean(&readed));
	if (readed == NULL)
		readed = ft_calloc(1, sizeof(char));
	if (ft_strchr(readed, '\n'))
		return (return_line(&readed));
	nb_readed = read_line(fd, &readed);
	if (nb_readed > 0 && *readed)
		return (return_line(&readed));
	return (clean(&readed));
}

static int	read_line(int fd, char **readed)
{
	char	buf[BUFFER_SIZE];
	int		total_buf;
	int		eof;

	total_buf = 0;
	eof = 0;
	while (! eof && ! ft_strchr(*readed, '\n'))
	{
		total_buf = read(fd, buf, BUFFER_SIZE);
		if (total_buf < 0)
			return (-1);
		else if (total_buf == 0)
			eof = 1;
		else
		{
			*readed = ft_strjoinbuf(*readed, buf, total_buf);
			if (! *readed)
				return (-1);
		}
	}
	return (1);
}

static char	*return_line(char **readed)
{
	char	*out;
	char	*tmp;
	size_t	line_size;

	if (ft_strchr(*readed, '\n'))
		line_size = ft_strchr(*readed, '\n') - *readed + 1;
	else
		line_size = ft_strlen(*readed);
	out = ft_substr(*readed, 0, line_size);
	if (! out)
		return (clean(readed));
	if (! ft_strchr(*readed, '\n'))
	{
		clean(readed);
		return (out);
	}
	tmp = ft_substr(*readed, line_size, ft_strlen(*readed) - line_size);
	free(*readed);
	if (! tmp)
		return (clean(&out));
	*readed = tmp;
	return (out);
}

static char	*clean(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
	return (NULL);
}
