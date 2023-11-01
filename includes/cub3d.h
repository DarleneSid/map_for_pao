/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/01 18:28:48 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <X11/X.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct t_data
{
	int		pos;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	int		row;
	int		h_map;
	int		cnt_1;
	int		height;
	int		len_map;
	int		len_path;
	int		no_here;
	int		so_here;
	int		we_here;
	int		ea_here;
	int		c_here;
	int		f_here;
	unsigned long		floor_color;
	unsigned long		ceiling_color;
	int		player_pos_x;
	int		player_pos_y;
	char	player_dir;
	char	*path;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	**map;
	char	**data;
	char	**work_map;
}			t_data;

/*		BORDER UTILS		*/
int	zero_or_letter(char c);
int	nospc(char c);
int	check_first_column(t_data *data);
int	check_last_column(t_data *data);
int	check_last_row(t_data *data);
/*		CHECKING BORDERS	*/
void	player_info(t_data *data, int x, int y);
int	longest_line_case(t_data *data, int x, int y, int len);
int	process_checking(t_data *data, int x, int y, int len);
int	check_borders(t_data *data);
/*		INIT N FREE			*/
int	init_map(t_data *data, int fd);
void	init_whos_here(t_data *data);
void	free_good_map(t_data *data);
void free_dstr(char **dstr);
/*		IS WHAT				*/
int	is_floor(t_data *data, char *s);
int	is_ceiling(t_data *data, char *s);
int	valid_for_path(char *s);
int	check_double_path(t_data *data, char *s, int i);
int	is_path(t_data *data, char *s);
/*		MAP					*/
int	height_of_map(int fd);
char	**check_map(t_data *data, int cur_row);
int	is_empty(t_data *data);
int	empty_row(char *s);
int	all_stuff_map(t_data *data);
int	check_all_inside(t_data *data);
int	parsing(t_data *data, char *file);
/*		UTILS				*/
int	invalid_start(t_data *data, char *s);
int	invalid_row(char *s);
int	check_valid_chars(t_data *data, char *s);
int	check_valid_char(char *s);
/*		WHAT THE PATH		*/
int	is_no(t_data *data);
int	is_so(t_data *data);
int	is_we(t_data *data);
int	is_ea(t_data *data);
int	set_path(t_data *data);

#endif
