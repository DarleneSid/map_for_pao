/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:01:30 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/08 19:36:48 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycasting_utils(t_ray *ray, t_player *p)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sdx = (p->px - ray->mapx) * ray->ddx;
	}
	else
	{
		ray->stepx = 1;
		ray->sdx = (ray->mapx + 1.0 - p->px) * ray->ddx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sdy = (p->py - ray->mapy) * ray->ddy;
	}
	else
	{
		ray->stepy = 1;
		ray->sdy = (ray->mapy + 1.0 - p->py) * ray->ddy;
	}
}

void	ft_raycasting(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sdx < ray->sdy)
		{
			ray->sdx += ray->ddx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sdy += ray->ddy;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapy < 1 || ray->mapx < 1 || ray->mapy > data->h_map - 1
			|| ray->mapx > ft_strlen(data->work_map[ray->mapy]) - 1)
			break ;
		else if (data->work_map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
}

void	wall_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sdx - ray->ddx);
	else
		ray->wall_dist = (ray->sdy - ray->ddy);
	ray->line_height = (int)(HEIGH / ray->wall_dist);
	ray->start = -(ray->line_height) / 2 + HEIGH / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + HEIGH / 2;
	if (ray->end >= HEIGH)
		ray->end = HEIGH - 1;
	if (ray->side == 0)
		ray->wall_x = player->py + ray->wall_dist * ray->diry;
	else
		ray->wall_x = player->px + ray->wall_dist * ray->dirx;
	ray->wall_x -= floor(ray->wall_x);
}

int	castallrays(t_player *player, t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(x, &(data->ray), player);
		ft_raycasting_utils(&(data->ray), player);
		ft_raycasting(data, &(data->ray));
		wall_height(&(data->ray), player);
		update_pixels(data, &(data->ray), x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (1);
}
