/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:59:41 by agirona           #+#    #+#             */
/*   Updated: 2021/08/28 18:33:49 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	secondary_error(int number)
{
	if (number == END_ERROR)
		ft_putstr("Missing end of level.");
	else if (number == SPAWN_ERROR)
		ft_putstr("The game can't start without a player, add a spawn point !");
	else if (number == COLLECT_ERROR)
	{
		ft_putstr("No item to collect is too easy =) ");
		ft_putstr("Add at least one to the map !");
	}
	else if (number == CLOSE_ERROR)
		ft_putstr("The map isn't closed !");
	else if (number == NIMB_ERROR)
		ft_putstr("There can be only one and unique Mr Nimbus !");
	else if (number == MALLOC_ERROR)
		ft_putstr("Malloc failed. :(");
}

int	error(int number)
{
	ft_putstr("Error\n");
	if (number == WIN_ERROR)
		ft_putstr("MLX failed window creation.");
	else if (number == IMG_ERROR)
		ft_putstr("MLX failed image creation.");
	else if (number == XPM_ERROR)
		ft_putstr("XPM creation failed.");
	else if (number == ARG_ERROR)
	{
		ft_putstr("Missing map or invalid map extension.");
		ft_putstr("\nUsage : ./so_long <map_name>.ber");
	}
	else if (number == RECT_ERROR)
		ft_putstr("The map is not a rectangle !");
	else if (number == CHAR_ERROR)
		ft_putstr("Invalid character in the map !");
	else
		secondary_error(number);
	return (0);
}
