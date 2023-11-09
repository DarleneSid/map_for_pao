/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:19:45 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/08 02:17:26 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	size_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->nbcol = 0;
	while (i < data->h_map)
	{
		j = ft_strlen(data->work_map[i]);
		if (j >= data->nbcol)
			data->nbcol = j - 1;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
		return (ft_printf("Wrong amount of arguments!\n"), 1);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub\0", 5))
		return (ft_printf("It has to end with .cub!\n"), 1);
	if (parsing(&data, av[1]))
		return (1);
	size_map(&data);
	init_game(&data);
	castallrays(&((&data)->p), &data);
	key_handler(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
