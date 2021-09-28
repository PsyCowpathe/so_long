/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:39:33 by agirona           #+#    #+#             */
/*   Updated: 2021/09/28 17:01:18 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_sprite(t_mlx *d)
{
	char	*str;
	int		width;
	int		y;
	int		x;

	width = 0;
	y = WIN_Y * 0.5 - 100;
	x = WIN_X * 0.5;
	mlx_put_image_to_window(d->mlx, d->win, d->xpm[d->frame].img, x, y);
	mlx_put_image_to_window(d->mlx, d->win, d->xpm[2].img, WIN_X - 90, 25);
	mlx_string_put(d->mlx, d->win, WIN_X - 100, 62, 0xFFFFFF, "x");
	if (d->collectible <= 9999)
	{
		str = ft_itoa(d->collectible);
		width = 7 * nb_len(d->collectible);
		mlx_string_put(d->mlx, d->win, WIN_X - 105 - width, 62, 0xFFFFFF, str);
		free(str);
	}
	else
		mlx_string_put(d->mlx, d->win, WIN_X - 125, 62, 0xFFFFFF, "NaN");
	width = 7 * nb_len(d->count);
	mlx_string_put(d->mlx, d->win, WIN_X - 100, 115, 0xFFFFFF, "x Movement");
	str = ft_itoa(d->count);
	mlx_string_put(d->mlx, d->win, WIN_X - 105 - width, 115, 0xFFFFFF, str);
	free(str);
}

void	print_portal(t_mlx *d)
{
	int		x;
	int		y;
	int		xc;
	int		yc;

	y = d->py - 11;
	if (y < 0)
		y = 0;
	while (y < d->py + 10 && y < d->mapy)
	{
		yc = (WIN_Y * 0.5) + 64 * (y - d->py);
		x = d->px - 16;
		if (x < 0)
			x = 0;
		while (x < d->px + 15 && x < d->mapx)
		{
			xc = (WIN_X * 0.5) - 64 * (d->px - x);
			if (d->map[y][x] == 'E' || d->map[y][x] == 'Z')
				mlx_put_image_to_window(d->mlx, d->win, d->xpm[3].img, xc, yc);
			if (d->map[y][x] == 'N' || d->map[y][x] == 'A')
				mr_nimbus(d, x, y);
			x++;
		}
		y++;
	}
}

void	print_map(t_mlx *d)
{
	int		x;
	int		y;
	int		xc;
	int		yc;

	y = new_ternaire(d->py - 12 < 0, d->py - 12, -1);
	while (++y < d->py + 10 && y < d->mapy)
	{
		yc = (WIN_Y * 0.5) + 64 * (y - d->py);
		x = new_ternaire(d->px - 17 < 0, d->px - 17, -1);
		while (++x < d->px + 15 && x < d->mapx)
		{
			xc = (WIN_X * 0.5) - 64 * (d->px - x);
			if (d->map[y][x] == '1')
				mlx_put_image_to_window(d->mlx, d->win, d->xpm[1].img, xc, yc);
			else
				mlx_put_image_to_window(d->mlx, d->win, d->xpm[0].img, xc, yc);
			if (d->map[y][x] == 'C' || d->map[y][x] == 'Y')
				mlx_put_image_to_window(d->mlx, d->win, d->xpm[2].img, xc, yc);
		}
	}
	print_portal(d);
	print_sprite(d);
}
