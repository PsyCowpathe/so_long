/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:10:13 by agirona           #+#    #+#             */
/*   Updated: 2021/09/08 22:10:45 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_size(t_mlx *data, int fd)
{
	char	*tmp;
	int		i;

	data->mapx = 0;
	data->mapy = 0;
	i = 0;
	while (get_next_line(fd, &tmp) == 1)
	{
		if (i++ == 0)
			data->mapx = ft_strlen(tmp);
		if ((int)ft_strlen(tmp) != data->mapx)
		{
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

int	collect_map(t_mlx *data, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (new_malloc((void *)&data->map, sizeof(char *), data->mapy) == 0)
		return (error(MALLOC_ERROR));
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
			return (error(MALLOC_ERROR));
		}
		i++;
	}
	free(tmp);
	return (1);
}

int	get_map(t_mlx *data, char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (get_map_size(data, fd) == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	if (collect_map(data, fd) == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
