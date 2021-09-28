/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:14:06 by agirona           #+#    #+#             */
/*   Updated: 2021/09/28 17:01:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moov_nimbus(t_mlx *d, int y, int *x)
{
	if (d->stuck == 0)
	{
		if (y - 3 > 0 && *x - 2 > 0 && d->map[y + 1][*x - 2] == '1'
			&& d->map[y - 2][*x - 2] == '0' && d->map[y - 3][*x - 2] == '0'
			&& d->map[y][*x - 2] == '0')
		{
			d->map[y][*x] = '0';
			d->map[y][*x - 1] = 'N';
		}
		else
			d->stuck = 1;
	}
	else
	{
		if (y - 3 > 0 && *x + 2 < d->mapx && d->map[y + 1][*x + 2] == '1'
			&& d->map[y - 2][*x + 2] == '0' && d->map[y - 3][*x + 2] == '0'
			&& d->map[y][*x + 2] == '0')
		{
			d->map[y][*x] = '0';
			d->map[y][*x + 1] = 'N';
			*x = *x + 1;
		}
		else
			d->stuck = 0;
	}
}

void	glitch_moov_nimbus(t_mlx *d, int y, int *x)
{
	if (d->stuck == 0)
	{
		if (y - 3 > 0 && *x - 2 > 0 && d->map[y + 1][*x - 2] == '1'
			&& d->map[y - 2][*x - 2] == 'X' && d->map[y - 3][*x - 2] == 'X'
			&& d->map[y][*x - 2] == 'X')
		{
			d->map[y][*x] = 'X';
			d->map[y][*x - 1] = 'A';
		}
		else
			d->stuck = 1;
	}
	else
	{
		if (y - 3 > 0 && *x + 2 < d->mapx && d->map[y + 1][*x + 2] == '1'
			&& d->map[y - 2][*x + 2] == 'X' && d->map[y - 3][*x + 2] == 'X'
			&& d->map[y][*x + 2] == 'X')
		{
			d->map[y][*x] = 'X';
			d->map[y][*x + 1] = 'A';
			*x = *x + 1;
		}
		else
			d->stuck = 0;
	}
}

void	enemy_and_collectible(t_mlx *data)
{
	int		y;
	int		x;

	y = 0;
	data->collectible = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == 'C' || data->map[y][x] == 'Y')
				data->collectible++;
			if (data->map[y][x] == 'N' && data->time % 3 == 0)
				moov_nimbus(data, y, &x);
			else if (data->map[y][x] == 'A' && data->time % 3 == 0)
				glitch_moov_nimbus(data, y, &x);
			x++;
		}
		y++;
	}
}

void	mr_nimbus(t_mlx *d, int x, int y)
{
	int		height;
	int		xc;
	int		yc;

	height = 25;
	if (d->nimbus == 1)
		height = 10;
	xc = (WIN_X * 0.5) - 64 * (d->px - x) - 64;
	yc = (WIN_Y * 0.5) + 64 * (y - d->py) - (197 + height);
	mlx_put_image_to_window(d->mlx, d->win, d->xpm[10 + d->nimbus].img, xc, yc);
	if (d->time % 5 == 0)
		d->nimbus++;
	if (d->nimbus == 4)
		d->nimbus = 0;
}
