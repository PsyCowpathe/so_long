/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:57:09 by agirona           #+#    #+#             */
/*   Updated: 2021/09/21 15:22:34 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	keypress(int key, t_mlx *data)
{
	if (key == KEY_W)
		data->forward = 1;
	if (key == KEY_D)
		data->right = 1;
	if (key == KEY_A)
		data->left = 1;
	if (key == KEY_S)
		data->backward = 1;
	if (key == KEY_ECHAP)
		exit_game(data);
	return (1);
}

int	keyrelease(int key, t_mlx *data)
{
	if (key == KEY_W)
		data->forward = 0;
	if (key == KEY_D)
		data->right = 0;
	if (key == KEY_A)
		data->left = 0;
	if (key == KEY_S)
		data->backward = 0;
	return (1);
}
