/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:01:01 by agirona           #+#    #+#             */
/*   Updated: 2021/09/28 17:21:09 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	gravity(t_mlx *d)
{
	if (d->endjump == 1 && d->py + 1 < d->mapy
		&& d->map[d->py + 1][d->px] != '1')
		d->py++;
	else if ((d->py - 2 > 0 && d->map[d->py - 2][d->px] != '1'
		&& d->map[d->py - 1][d->px] != '1' && d->up == 1) || d->endjump == 0)
	{
		d->endjump = 0;
		if (d->jump <= 5 && d->py > 0
			&& d->map[d->py - 2][d->px] != '1')
		{
			d->jump++;
			d->py--;
		}
		else if (d->py > 0 && d->map[d->py - 2][d->px] == '1')
			d->jump = 6;
		if (d->jump > 5)
		{	
			if (++d->count != 1)
				ft_putchar(' ');
			ft_putnbr(d->count);
			d->jump = 0;
			d->endjump = 1;
		}
	}
}

void	moov(t_mlx *data, int savex, int savey)
{
	if (data->endjump == 1 && data->backward == 1 && data->py + 3 < data->mapy
		&& data->map[data->py + 1][data->px] == '1'
		&& ft_ischar("0CE", data->map[data->py + 2][data->px]) == 1
		&& ft_ischar("0CE", data->map[data->py + 3][data->px]) == 1)
		data->py += 2;
	if (data->left == 1 && data->map[data->py][data->px - 1] != '1'
	&& data->map[data->py - 1][data->px - 1] != '1')
	{
		data->direction = 1;
		data->px -= 1;
	}
	if (data->right == 1 && data->map[data->py][data->px + 1] != '1'
		&& data->map[data->py - 1][data->px + 1] != '1')
	{
		data->direction = 0;
		data->px += 1;
	}
	if (savex != data->px || savey != data->py)
	{	
		if (++data->count != 1)
			ft_putchar(' ');
		ft_putnbr(data->count);
	}
}

void	physics(t_mlx *data)
{
	if (choose_walk_frame(data) == 0)
		return ;
	hit_box(data);
	new_dimension(data);
	gravity(data);
	moov(data, data->px, data->py);
	collectible(data);
}
