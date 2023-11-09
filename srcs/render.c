/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:03:25 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/08 22:23:06 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_side(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dirx < 0)
			return (W);
		else
			return (E);
	}
	else
	{
		if (ray->diry > 0)
			return (S);
		else
			return (N);
	}
}

void	update_pixels(t_data *data, t_ray *ray, int x)
{
	int			y;
	int			n;
	int			color;
	int			coord[2];

	y = 0;
	n = ft_side(ray);
	coord[0] = (int)(ray->wall_x * data->s);
	if ((ray->side == 0 && ray->dirx < 0) || (ray->side == 1 && ray->diry > 0))
		coord[0] = data->s - coord[0] - 1;
	ray->step = 1.0 * data->s / ray->line_height;
	ray->pos = (ray->start - HEIGH / 2 + ray->line_height / 2) * ray->step;
	while (y <= HEIGH / 2 && y < ray->start)
		img_pix_put(data->img, x, y++, data->ceiling_color);
	while (y < ray->end)
	{
		coord[1] = (int)ray->pos;
		color = data->texture[n].add[data->s * coord[1] + coord[0]];
		img_pix_put(data->img, x, y, color);
		ray->pos += ray->step;
		y++;
	}
	while (y > HEIGH / 2 && y < HEIGH - 1)
		img_pix_put(data->img, x, y++, data->floor_color);
}

int	render(t_data *data)
{
	move_player(data);
	castallrays(&((data)->p), data);
	return (0);
}
