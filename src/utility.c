/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:58:05 by agirona           #+#    #+#             */
/*   Updated: 2021/08/28 19:20:35 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_mlx *data, int phase)
{
	int		i;

	i = 0;
	if (data->map != NULL)
	{
		while (i != data->mapy)
			free(data->map[i++]);
		free(data->map);
	}
	i = 0;
	while (phase >= 1 && i < 15)
	{
		if (data->xpm[i].img != NULL)
			mlx_destroy_image(data->mlx, data->xpm[i].img);
		i++;
	}
	if (phase >= 1)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
	}
	exit(EXIT_SUCCESS);
	return (1);
}

int	nb_len(unsigned int nb)
{
	int		count;

	count = 1;
	while (nb / 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

void	init_struct(t_mlx *data)
{
	data->map = NULL;
	data->forward = 0;
	data->right = 0;
	data->left = 0;
	data->backward = 0;
	data->frame = 4;
	data->moov = 0;
	data->collectible = 0;
	data->count = 0;
	data->jump = 0;
	data->endjump = 1;
	data->direction = 1;
	data->nimbus = 0;
	data->stuck = 0;
	data->time = 0;
}
