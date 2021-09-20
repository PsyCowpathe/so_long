/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:11:19 by agirona           #+#    #+#             */
/*   Updated: 2021/09/20 16:47:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_data(t_mlx *data, int *player, int *nimbus, int *end)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->mapy)
	{
		x = -1;
		while (++x < data->mapx)
		{
			if (ft_ischar("10NCPE", data->map[y][x]) == 0)
				return (error(CHAR_ERROR));
			if (data->map[y][x] == 'C')
				data->collectible++;
			else if (data->map[y][x] == 'E')
				*end = *end + 1;
			else if (data->map[y][x] == 'P')
				*player = *player + 1;
			else if (data->map[y][x] == 'N')
				*nimbus = *nimbus + 1;
		}
	}
	return (1);
}

void	clean_map(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == 'V')
				data->map[y][x] = '0';
			else if (data->map[y][x] == 'G')
				data->map[y][x] = 'C';
			else if (data->map[y][x] == 'F')
				data->map[y][x] = 'E';
			else if (data->map[y][x] == 'O')
				data->map[y][x] = 'N';
			else if (data->map[y][x] == 'M')
				data->map[y][x] = 'P';
			x++;
		}
		y++;
	}
}

void	get_player_pos(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
			}
			x++;
		}
		y++;
	}
}
