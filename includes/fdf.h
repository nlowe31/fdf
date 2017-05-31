/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:33:02 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/31 18:32:10 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define WIN_HEIGHT	1200
# define WIN_WIDTH	2000
# define IMG_HEIGHT	1200
# define IMG_WIDTH	2000

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_coord;

typedef struct		s_env
{
	void			*core;
	void			*win;
	t_coord			**map;
	void			*img;
	char			*data;
	int				bpp;
	int				ls;
	int				en;
	int				x_max;
	int				y_max;
	int				x_scale;
	int				y_scale;
	int				z_scale;
	int				x_move;
	int				y_move;
}					t_env;

typedef struct		s_seg
{
	int				x_0;
	int				x_1;
	int				y_0;
	int				y_1;
	int				d_x;
	int				d_y;
	int				s_x;
	int				s_y;
	int				err1;
	int				err2;
}					t_seg;

void	print_map(t_coord **map, t_env *env);



void				fdf_error(char *message);
char				*get_map(char *filename);

t_coord				**parse(char **str, t_env *env);
void				check_map(char *str, int *x_max, int *y_max);



#endif