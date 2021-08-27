/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 23:49:19 by agirona           #+#    #+#             */
/*   Updated: 2021/08/27 22:41:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		get_map_size(t_mlx *data, char *str)
{
	int		fd;
	char	*tmp;
	int		i;

	data->mapx = 0;
	data->mapy = 0;
	i = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &tmp) == 1)
	{
		if (i++ == 0)
			data->mapx = ft_strlen(tmp);
		if ((int)ft_strlen(tmp) != data->mapx)
		{
			close(fd);
			free(tmp);
			return (error(RECT_ERROR));
		}
		free(tmp);
		data->mapy++;
	}
	free(tmp);
	close(fd);
	return (1);
}

int		get_map(t_mlx *data, char *str)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	if (get_map_size(data, str) == 0)
		return (0);
	if (new_malloc((void *)&data->map, sizeof(char *), data->mapy) == 0)
		return (error(MALLOC_ERROR));
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &tmp) == 1)
	{
		data->map[i] = ft_strdup(tmp);
		free(tmp);
		if (data->map[i] == NULL)
		{
			while (i >= 0)
				free(data->map[i--]);
			free(data->map);
			data->map = NULL;
			close(fd);
			return (error(MALLOC_ERROR));
		}
		i++;
	}
	free(tmp);
	close(fd);
	return (1);
}

int		verif_char(t_mlx *data, int player, int end, int nimbus)
{
	if (end == 0)
		return (error(END_ERROR));
	if (player != 1)
		return (error(SPAWN_ERROR));
	if (data->collectible == 0)
		return (error(COLLECT_ERROR));
	if (nimbus > 1)
		return (error(NIMB_ERROR));
	return (1);
}

int		spam_fill(t_mlx *data, char **map, int x, int y)
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

int		parsing(t_mlx *data)
{
	int		x;
	int		y;
	int		player;
	int		end;
	int		nimbus;

	y = 0;
	player = 0;
	end = 0;
	nimbus = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (ft_ischar("10NCPE", data->map[y][x]) == 0)
				return (error(CHAR_ERROR));
			if (data->map[y][x] == 'C')
				data->collectible++;
			else if (data->map[y][x] == 'E')
				end++;
			else if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
				player++;
			}
			else if (data->map[y][x] == 'N')
				nimbus++;
			x++;
		}
		y++;
	}
	if (verif_char(data, player, end, nimbus) == 0)
		return (0);
	if (spam_fill(data, data->map, data->px, data->py) == 0)
		return (error(CLOSE_ERROR));
	clean_map(data);
	return (1);
}
