/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:01:01 by agirona           #+#    #+#             */
/*   Updated: 2021/08/28 18:33:48 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	gravity(t_mlx *data)
{
	if (data->endjump == 1 && data->py + 1 < data->mapy
		&& data->map[data->py + 1][data->px] != '1')
		data->py++;
	else if ((data->py - 2 > 0 && data->map[data->py - 2][data->px] != '1'
		&& data->forward == 1) || data->endjump == 0)
	{
		data->endjump = 0;
		if (data->jump <= 5 && data->py > 0
			&& data->map[data->py - 2][data->px] != '1')
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

void	moov(t_mlx *data)
{
	if (data->endjump == 1 && data->backward == 1 && data->py + 3 < data->mapy
		&& data->map[data->py + 1][data->px] == '1'
		&& ft_ischar("0CE", data->map[data->py + 2][data->px]) == 1
		&& ft_ischar("0CE", data->map[data->py + 3][data->px]) == 1)
	{
		data->py += 2;
		data->count++;
	}
	if (data->left == 1 && data->map[data->py][data->px - 1] != '1'
	&& data->map[data->py - 1][data->px - 1] != '1' && ++data->count)
	{
		data->direction = 1;
		data->px -= 1;
	}
	if (data->right == 1 && data->map[data->py][data->px + 1] != '1'
		&& data->map[data->py - 1][data->px + 1] != '1' && ++data->count)
	{
		data->direction = 0;
		data->px += 1;
	}
}

void	physics(t_mlx *data)
{
	if (choose_walk_frame(data) == 0)
		return ;
	hit_box(data);
	new_dimension(data);
	gravity(data);
	moov(data);
	collectible(data);
}
