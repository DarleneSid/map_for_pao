/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:54:34 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/08 20:52:05 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	init_ray(int x, t_ray *ray, t_player *player)
{
	ft_memset(ray, 0, sizeof(ray));
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dirx = player->dirx + player->planex * ray->camera_x;
	ray->diry = player->diry + player->planey * ray->camera_x;
	ray->mapx = (int)player->px;
	ray->mapy = (int)player->py;
	ray->ddx = fabs(1 / ray->dirx);
	ray->ddy = fabs(1 / ray->diry);
}

int	init_texture(t_data *d, t_tex *tex)
{
	tex[N].img = mlx_xpm_file_to_image(d->mlx, d->no_path, &(d->s), &(d->s));
	tex[S].img = mlx_xpm_file_to_image(d->mlx, d->so_path, &(d->s), &(d->s));
	tex[E].img = mlx_xpm_file_to_image(d->mlx, d->ea_path, &(d->s), &(d->s));
	tex[W].img = mlx_xpm_file_to_image(d->mlx, d->we_path, &(d->s), &(d->s));
	if (!tex[N].img || ! tex[S].img || !tex[E].img || !tex[W].img)
		return (1);
	tex[N].add = (int *)mlx_get_data_addr(tex[N].img, &(tex[N].bpp),
			&(tex[N].line_length), &(tex[N].endian));
	tex[S].add = (int *)mlx_get_data_addr(tex[S].img, &(tex[S].bpp),
			&(tex[S].line_length), &(tex[S].endian));
	tex[E].add = (int *)mlx_get_data_addr(tex[E].img, &(tex[E].bpp),
			&(tex[E].line_length), &(tex[E].endian));
	tex[W].add = (int *)mlx_get_data_addr(tex[W].img, &(tex[W].bpp),
			&(tex[W].line_length), &(tex[W].endian));
	if (!tex[N].add || !tex[S].add || !tex[E].add || !tex[W].add)
		return (1);
	return (0);
}

void	init_game(t_data *d)
{
	init_player(d);
	d->mlx = mlx_init();
	if (!d->mlx)
		close_window(d);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGH, "cub3D");
	if (!d->win)
		close_window(d);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGH);
	if (!d->img)
		close_window(d);
	d->add = mlx_get_data_addr(d->img, &d->bpp, &d->line_length, &d->endian);
	if (!d->add)
		close_window(d);
	if (init_texture (d, d->texture))
		close_window(d);
	mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGH / 2);
}

int	close_window(t_data *d)
{
	if (d->mlx)
	{
		if (d->win)
			mlx_destroy_window(d->mlx, d->win);
		if (d->img)
			mlx_destroy_image(d->mlx, d->img);
		if (d->texture[N].img)
			mlx_destroy_image(d->mlx, d->texture[N].img);
		if (d->texture[S].img)
			mlx_destroy_image(d->mlx, d->texture[S].img);
		if (d->texture[E].img)
			mlx_destroy_image(d->mlx, d->texture[E].img);
		if (d->texture[W].img)
			mlx_destroy_image(d->mlx, d->texture[W].img);
		mlx_destroy_display(d->mlx);
		mlx_loop_end(d->mlx);
		free(d->mlx);
	}
	free_good_map(d);
	exit (0);
	return (0);
}
