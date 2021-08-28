/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 19:25:57 by agirona           #+#    #+#             */
/*   Updated: 2021/08/28 18:15:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	refresh(t_mlx *data)
{
	int		save;

	save = data->count;
	clear_window(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	physics(data);
	moov_enemy(data);
	print_map(data);
	data->time++;
	if (data->count != save)
	{
		if (data->count != 1)
			ft_putchar(' ');
		ft_putnbr(data->count);
	}
	if (data->time == 10)
		data->time = 0;
	if (data->count >= 1000000)
		exit_game(data, 1);
	return (1);
}

int	main(int argc, char **argv)
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