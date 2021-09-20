/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:56:03 by agirona           #+#    #+#             */
/*   Updated: 2021/09/20 19:54:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, "Peace among worlds");
	if (data->win == NULL)
		return (error(WIN_ERROR));
	data->img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (error(IMG_ERROR));
	}
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits, &data->linelen, &data->endian);
	return (1);
}

void	secondary_file_to_img(t_mlx *data)
{
	data->xpm[8].img = mlx_xpm_file_to_image(data->mlx,
			REV_OUCH, &data->xpm[8].width, &data->xpm[8].height);
	data->xpm[9].img = mlx_xpm_file_to_image(data->mlx,
			REV_WALK, &data->xpm[9].width, &data->xpm[9].height);
	data->xpm[10].img = mlx_xpm_file_to_image(data->mlx,
			NIMBUS1, &data->xpm[10].width, &data->xpm[10].height);
	data->xpm[11].img = mlx_xpm_file_to_image(data->mlx,
			NIMBUS2, &data->xpm[11].width, &data->xpm[11].height);
	data->xpm[12].img = mlx_xpm_file_to_image(data->mlx,
			NIMBUS3, &data->xpm[12].width, &data->xpm[12].height);
	data->xpm[13].img = mlx_xpm_file_to_image(data->mlx,
			NIMBUS4, &data->xpm[13].width, &data->xpm[13].height);
	data->xpm[14].img = mlx_xpm_file_to_image(data->mlx,
			NIMBUS5, &data->xpm[14].width, &data->xpm[14].height);
}

void	file_to_img(t_mlx *data)
{
	data->xpm[0].img = mlx_xpm_file_to_image(data->mlx,
			GRASS, &data->xpm[0].width, &data->xpm[0].height);
	data->xpm[1].img = mlx_xpm_file_to_image(data->mlx,
			WALL, &data->xpm[1].width, &data->xpm[1].height);
	data->xpm[2].img = mlx_xpm_file_to_image(data->mlx,
			SEED, &data->xpm[2].width, &data->xpm[2].height);
	data->xpm[3].img = mlx_xpm_file_to_image(data->mlx,
			PORTAL, &data->xpm[3].width, &data->xpm[3].height);
	data->xpm[4].img = mlx_xpm_file_to_image(data->mlx,
			CLASSIC, &data->xpm[4].width, &data->xpm[4].height);
	data->xpm[5].img = mlx_xpm_file_to_image(data->mlx,
			OUCH, &data->xpm[5].width, &data->xpm[5].height);
	data->xpm[6].img = mlx_xpm_file_to_image(data->mlx,
			WALK, &data->xpm[6].width, &data->xpm[6].height);
	data->xpm[7].img = mlx_xpm_file_to_image(data->mlx,
			REV_CLASSIC, &data->xpm[7].width, &data->xpm[7].height);
	secondary_file_to_img(data);
}

int	init_texture(t_mlx *data)
{
	int		i;

	file_to_img(data);
	i = 0;
	while (i < 15)
	{
		if (data->xpm[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(data->mlx, data->xpm[i].img);
			return (error(XPM_ERROR));
		}
		i++;
	}
	return (1);
}

void	clear_window(t_mlx *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			data->addr[y * WIN_X + x] = 0x5D6D7E;
			x++;
		}
		y++;
	}
}
