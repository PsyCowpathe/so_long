/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 23:49:19 by agirona           #+#    #+#             */
/*   Updated: 2021/09/22 18:56:19 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	spam_fill(t_mlx *data, char **map, int x, int y)
{
	if (x < 0 || x >= data->mapx || y < 0 || y >= data->mapy)
		return (0);
	if (ft_ischar("1MFOGV", map[y][x]) == 1)
		return (1);
	if (map[y][x] == '0')
		map[y][x] = 'V';
	else if (map[y][x] == 'C')
		map[y][x] = 'G';
	else if (map[y][x] == 'E')
		map[y][x] = 'F';
	else if (map[y][x] == 'N')
		map[y][x] = 'O';
	else if (map[y][x] == 'P')
		map[y][x] = 'M';
	if (spam_fill(data, map, x + 1, y) == 1
		&& spam_fill(data, map, x - 1, y) == 1
		&& spam_fill(data, map, x, y + 1) == 1
		&& spam_fill(data, map, x, y - 1) == 1)
		return (1);
	else
		return (0);
}

int	verif_char(t_mlx *data, int player, int end, int nimbus)
{
	if (end == 0)
		return (error(END_ERROR));
	if (player < 1)
		return (error(SPAWN_ERROR));
	if (player > 1)
		return (error(MULT_ERROR));
	if (data->collectible == 0)
		return (error(COLLECT_ERROR));
	if (nimbus > 1)
		return (error(NIMB_ERROR));
	return (1);
}

void	no_glitch(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == '0')
				data->map[y][x] = 'X';
			x++;
		}
		y++;
	}
}

int	parsing(t_mlx *data)
{
	int		player;
	int		end;
	int		nimbus;

	player = 0;
	end = 0;
	nimbus = 0;
	get_player_pos(data);
	if (get_map_data(data, &player, &nimbus, &end) == 0)
		return (0);
	if (verif_char(data, player, end, nimbus) == 0)
		return (0);
	if (spam_fill(data, data->map, data->px, data->py) == 0)
		return (error(CLOSE_ERROR));
	no_glitch(data);
	clean_map(data);
	return (1);
}
