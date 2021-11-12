/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:14:04 by ycornamu          #+#    #+#             */
/*   Updated: 2021/11/12 17:03:25 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mtx_mul(double a[3][3], double b[3][1])
{
	int		i;
	int		j;
	int		k;
	double	res[3][1];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 1)
		{
			k = 0;
			res[i][j] = 0;
			while (k < 3)
			{
				res[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	b[0][0] = res[0][0];
	b[1][0] = res[1][0];
	b[2][0] = res[2][0];
}

void	mtx_setline(double line[3][3], double a, double b, double c)
{
	(*line)[0] = a;
	(*line)[1] = b;
	(*line)[2] = c;
}
