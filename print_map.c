/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:39:33 by agirona           #+#    #+#             */
/*   Updated: 2021/08/27 22:41:09 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_sprite(t_mlx *data)
{
	char	*str;
	int		width;

	width = 0;
	mlx_put_image_to_window(data->mlx, data->win, data->xpm[data->frame].img, WIN_X * 0.5, WIN_Y * 0.5 - 100);
	mlx_put_image_to_window(data->mlx, data->win, data->xpm[2].img, WIN_X - 90, 25);
	mlx_string_put(data->mlx, data->win, WIN_X - 100, 62, 0xFFFFFF, "x");
	if (data->collectible <= 9999)
	{
		str = ft_itoa(data->collectible);
		width = 7 * nb_len(data->collectible);
		mlx_string_put(data->mlx, data->win, WIN_X - 105 - width, 62, 0xFFFFFF, str);
		free(str);
	}
	else
		mlx_string_put(data->mlx, data->win, WIN_X - 125, 62, 0xFFFFFF, "NaN");
	width = 7 * nb_len(data->count);
	mlx_string_put(data->mlx, data->win, WIN_X - 100, 115, 0xFFFFFF, "x Movement");
	str = ft_itoa(data->count);
	mlx_string_put(data->mlx, data->win, WIN_X - 105 - width, 115, 0xFFFFFF, str);
	free(str);
}

void	mr_nimbus(t_mlx *data, int x, int y)
{
	int		height;

	height = 25;
	if (data->nimbus == 1)
		height = 10;
	mlx_put_image_to_window(data->mlx, data->win, data->xpm[10 + data->nimbus].img, (WIN_X * 0.5) - 64 * (data->px - x) - 64, (WIN_Y * 0.5) + 64 * (y - data->py) - (197 + height));
	if (data->time % 5 == 0)
		data->nimbus++;
	if (data->nimbus == 4)
		data->nimbus = 0;
}

void	print_portal(t_mlx *data)
{
	int		x;
	int		y;

	y = data->py - 11;
	if (y < 0)
		y = 0;
	while (y < data->py + 10 && y < data->mapy)
	{
		x = data->px - 16;
		if (x < 0)
			x = 0;
		while (x < data->px + 15 && x < data->mapx)
		{
			if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->xpm[3].img, (WIN_X * 0.5) - 64 * (data->px - x), (WIN_Y * 0.5) + 64 * (y - data->py));
			if (data->map[y][x] == 'N')
				mr_nimbus(data, x, y);

			x++;
		}
		y++;
	}
}

void	print_map(t_mlx *data)
{
	int		x;
	int		y;

	y = data->py - 11;
	if (y < 0)
		y = 0;
	while (y < data->py + 10 && y < data->mapy)
	{
		x = data->px - 16;
		if (x < 0)
			x = 0;
		while (x < data->px + 15 && x < data->mapx)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->xpm[1].img, (WIN_X * 0.5) - 64 * (data->px - x), (WIN_Y * 0.5) + 64 * (y - data->py));
			else
				mlx_put_image_to_window(data->mlx, data->win, data->xpm[0].img, (WIN_X * 0.5) - 64 * (data->px - x), (WIN_Y * 0.5) + 64 * (y - data->py));
			if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->xpm[2].img, (WIN_X * 0.5) - 64 * (data->px - x), (WIN_Y * 0.5) + 64 * (y - data->py));
			x++;
		}
		y++;
	}
	print_portal(data);
	print_sprite(data);
}
