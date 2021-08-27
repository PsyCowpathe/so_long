/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 19:25:57 by agirona           #+#    #+#             */
/*   Updated: 2021/08/27 22:41:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moov_nimbus(t_mlx *data, int y, int *x)
{
	if (data->stuck == 0)
	{
		if (y - 3 > 0 && *x - 2 > 0 && data->map[y + 1][*x - 2] == '1' && data->map[y - 2][*x - 2] != '1'
			&& data->map[y - 3][*x - 2] != '1' && data->map[y][*x - 2] != '1')
		{
			data->map[y][*x] = '0';
			data->map[y][*x - 1] = 'N';
		}
		else
			data->stuck = 1;
	}
	else
	{
		if (y - 3 > 0 && *x + 2 < data->mapx && data->map[y + 1][*x + 2] == '1' && data->map[y - 2][*x + 2] != '1'
			&& data->map[y - 3][*x + 2] != '1' && data->map[y][*x + 2] != '1')
		{
			data->map[y][*x] = '0';
			data->map[y][*x + 1] = 'N';
			*x = *x + 1;
		}
		else
			data->stuck = 0;
	}
}

void	moov_enemy(t_mlx *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == 'N' && data->time % 3 == 0)
				moov_nimbus(data, y, &x);
			x++;
		}
		y++;
	}
}

int		refresh(t_mlx *data)
{
	clear_window(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	event(data);
	moov_enemy(data);
	print_map(data);
	data->time++;
	if (data->time == 10)
		data->time = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	data;

	if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber") != 0)
		return (error(ARG_ERROR));
	init_struct(&data);	
	if (init_mlx(&data) == 0)
		exit_game(&data, 0);
	if (init_texture(&data) == 0)
		exit_game(&data, 0);
	if (get_map(&data, argv[1]) == 0)
		exit_game(&data, 1);
	if (parsing(&data) != 1)
		exit_game(&data, 1);
	mlx_hook(data.win, 2, 1L << 0, keypress, &data);
	mlx_hook(data.win, 3, 1L << 1, keyrelease, &data);
	mlx_hook(data.win, 17, (1L << 17), exit_game, NULL);
	mlx_loop_hook(data.mlx, &refresh, &data);
	mlx_loop(data.mlx);
	return (1);
}
