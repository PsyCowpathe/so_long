/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:08:44 by agirona           #+#    #+#             */
/*   Updated: 2021/09/28 17:21:10 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collectible(t_mlx *data)
{
	if (data->map[data->py][data->px] == 'C'
		|| data->map[data->py - 1][data->px] == 'C')
	{
		if (data->map[data->py - 1][data->px] == 'C')
			data->map[data->py - 1][data->px] = '0';
		if (data->map[data->py][data->px] == 'C')
			data->map[data->py][data->px] = '0';
		if (data->direction == 0)
			data->frame = 5;
		else
			data->frame = 8;
	}	
}

void	new_dimension(t_mlx *data)
{
	if (data->collectible == 0 && (data->map[data->py][data->px] == 'E'
		|| data->map[data->py - 1][data->px] == 'E'))
	{
		if (data->endjump == 0)
		{
			if (++data->count != 1)
				ft_putchar(' ');
			ft_putnbr(data->count);
		}
		exit_game(data);
	}
}

int	choose_walk_frame(t_mlx *data)
{
	if (data->up == 1 || data->backward == 1
		|| data->left == 1 || data->right == 1)
	{
		if (data->time % 2 != 0)
			return (0);
		if (data->direction == 0 && data->time % 4 == 0)
		{
			if (data->frame == 4)
				data->frame = 6;
			else
				data->frame = 4;
		}
		else if (data->time % 4 == 0)
		{
			if (data->frame == 7)
				data->frame = 9;
			else
				data->frame = 7;
		}
	}
	return (1);
}

void	hit_box(t_mlx *data)
{
	int		x;
	int		y;

	y = data->py - 1;
	if (data->py < 0)
		data->py = 0;
	while (y < data->py + 3 && y < data->mapy)
	{
		x = data->px - 1;
		if (data->px < 0)
			data->px = 0;
		while (x < data->px + 2 && x < data->mapx)
		{
			if (data->map[y][x] == 'N')
				exit_game(data);
			x++;
		}
		y++;
	}
}
