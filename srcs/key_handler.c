/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:55:39 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/08 16:55:08 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int key, t_data *data)
{
	if (key == 65307)
		close_window(data);
	if (key == 65361)
		data->p.rot -= 1;
	if (key == 65363)
		data->p.rot += 1;
	if (key == 119)
		data->p.movey = 1;
	if (key == 97)
		data->p.movex = -1;
	if (key == 115)
		data->p.movey = -1;
	if (key == 100)
		data->p.movex = 1;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == 65307)
		close_window(data);
	if (key == 119 && data->p.movey == 1)
		data->p.movey = 0;
	if (key == 115 && data->p.movey == -1)
		data->p.movey = 0;
	if (key == 97 && data->p.movex == -1)
		data->p.movex += 1;
	if (key == 100 && data->p.movex == 1)
		data->p.movex -= 1;
	if (key == 65361 && data->p.rot <= 1)
		data->p.rot = 0;
	if (key == 65363 && data->p.rot >= -1)
		data->p.rot = 0;
	return (0);
}

void	key_handler(t_data *data)
{
	mlx_hook(data->win, 33, NoEventMask, close_window, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release_handler, data);
}
