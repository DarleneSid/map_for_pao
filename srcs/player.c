/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:58:55 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/08 21:34:19 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	ft_memset(&(data->p), 0, sizeof(data->p));
	data->p.px = data->player_pos_y + 0.5;
	data->p.py = data->player_pos_x + 0.5;
	if (data->player_dir == 'S')
	{
		data->p.diry = 1;
		data->p.planex = -0.66;
	}
	else if (data->player_dir == 'N')
	{
		data->p.diry = -1;
		data->p.planex = 0.66;
	}
	if (data->player_dir == 'W')
	{
		data->p.dirx = -1;
		data->p.planey = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->p.dirx = 1;
		data->p.planey = 0.66;
	}
}

int	rotate_player(double rotdir, t_player *p)
{
	int		moved;
	double	tmp;
	double	rot;

	moved = 0;
	rot = ROTS * rotdir;
	tmp = p->dirx;
	p->dirx = p->dirx * cos(rot) - p->diry * sin(rot);
	p->diry = tmp * sin(rot) + p->diry * cos(rot);
	tmp = p->planex;
	p->planex = p->planex * cos(rot) - p->planey * sin(rot);
	p->planey = tmp * sin(rot) + p->planey * cos(rot);
	return (1);
}

void	is_wall(t_data *data, double newx, double newy)
{
	if (newx > 1 && newx < data->nbcol)
	{
		if (data->work_map[(int)newy][(int)newx] == '1'
			&& data->work_map[(int)newy][(int)newx] != ' ')
			return ;
		data->p.px = newx;
	}
	if (newy > 1 && newy < data->h_map
		&& data->work_map[(int)newy][(int)newx] != ' ')
	{
		if (data->work_map[(int)newy][(int)newx] == '1')
			return ;
		data->p.py = newy;
	}
}

void	move_player(t_data *data)
{
	if (data->p.movey == 1)
	{
		data->p.newx = data->p.px + data->p.dirx * MOVES;
		data->p.newy = data->p.py + data->p.diry * MOVES;
	}
	if (data->p.movey == -1)
	{
		data->p.newx = data->p.px - data->p.dirx * MOVES;
		data->p.newy = data->p.py - data->p.diry * MOVES;
	}
	if (data->p.movex == -1)
	{
		data->p.newx = data->p.px + data->p.diry * MOVES;
		data->p.newy = data->p.py - data->p.dirx * MOVES;
	}
	if (data->p.movex == 1)
	{
		data->p.newx = data->p.px - data->p.diry * MOVES;
		data->p.newy = data->p.py + data->p.dirx * MOVES;
	}
	if (data->p.rot != 0)
		rotate_player(data->p.rot, &(data->p));
	is_wall(data, data->p.newx, data->p.newy);
}
