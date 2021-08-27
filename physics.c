/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:01:01 by agirona           #+#    #+#             */
/*   Updated: 2021/08/27 22:41:10 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	gravity(t_mlx *data)
{
	if (data->endjump == 1 && data->py + 1 < data->mapy && data->map[data->py + 1][data->px] != '1')
		data->py++;
	else if ((data->py - 2 > 0 && data->map[data->py - 2][data->px] != '1' && data->forward == 1) || data->endjump == 0)
	{
		data->endjump = 0;
		if (data->jump <= 5 && data->py > 0 && data->map[data->py - 2][data->px] != '1')
		{
			data->jump++;
			data->py--;
		}
		else if (data->py > 0 && data->map[data->py - 2][data->px] == '1')
				data->jump = 6;
		if (data->jump > 5)
		{
			data->count++;
			data->jump = 0;
			data->endjump = 1;
		}
	}
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
				exit_game(data, 1);
			x++;
		}
		y++;
	}
}

int		event(t_mlx *data)
{
	int		save;

	if (data->forward == 1 || data->backward == 1 || data->left == 1 || data->right == 1)
	{
		if (data->time % 2 != 0)
			return (1);
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
	hit_box(data);
	save = data->count;
	if (data->collectible == 0 && (data->map[data->py][data->px] == 'E' || data->map[data->py - 1][data->px] == 'E'))
		exit_game(data, 1);
	gravity(data);
	if (data->endjump == 1 && data->backward == 1 && data->py + 3 < data->mapy && data->map[data->py + 1][data->px] == '1'
		&& (data->map[data->py + 2][data->px] == '0' || data->map[data->py + 2][data->px] == 'C' || data->map[data->py + 2][data->px] == 'E')
		&& (data->map[data->py + 3][data->px] == '0' || data->map[data->py + 3][data->px] == 'C' || data->map[data->py + 3][data->px] == 'E'))
	{
		data->py += 2;
		data->count++;
	}
	if (data->left == 1 && data->map[data->py][data->px - 1] != '1' && data->map[data->py - 1][data->px - 1] != '1' && ++data->count)
	{
		data->direction = 1;
		data->px -= 1;
	}
	if (data->right == 1 && data->map[data->py][data->px + 1] != '1' && data->map[data->py - 1][data->px + 1] != '1' && ++data->count)
	{
		data->direction = 0;
		data->px += 1;
	}
	if (data->map[data->py][data->px] == 'C' || data->map[data->py - 1][data->px] == 'C')
	{
		if (data->map[data->py - 1][data->px] == 'C')
			data->map[data->py - 1][data->px] = '0';
		if (data->map[data->py][data->px] == 'C')
			data->map[data->py][data->px] = '0';
		if (data->direction == 0)
			data->frame = 5;
		else
			data->frame = 8;
		data->collectible--;
	}
	if (data->count != save)
	{
		if (data->count != 1)
			ft_putchar(' ');
		ft_putnbr(data->count);
	}
	if (data->count >= 1000000)
		exit_game(data, 1);
	return (1);
}
