/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:41 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/20 19:06:43 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE], const size_t s2_size);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

char	*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE], const size_t s2_size)
{
	size_t	i;
	size_t	s1_size;
	char	*out;

	if (! s1 || ! s2)
		return (NULL);
	i = -1;
	s1_size = ft_strlen(s1);
	out = calloc(s1_size + s2_size + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	while (++i < s1_size)
		*(out + i) = *(s1 + i);
	--i;
	while (++i < (s1_size + s2_size))
		*(out + i) = *(s2 + i - s1_size);
	free(s1);
	return (out);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*out;

	i = 0;
	out = malloc(count * size);
	if (out == NULL)
		return (NULL);
	while (i < count)
		*(out + i++) = 0;
	return (out);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i) != 0)
		if (*(s + i++) == (char)(c))
			return ((char *)(s + --i));
	if (*(s + i) == c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*out;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	out = calloc((len + 1), sizeof(char));
	if (out == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < start)
			i++;
		while (i < (len + start))
		{
			*(out + i - start) = *(s + i);
			i++;
		}
	}
	return (out);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != 0)
		i++;
	return (i);
}
