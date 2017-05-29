/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:33:02 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:11:08 by nlowe            ###   ########.fr       */
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
	int				x_move;
	int				y_move;
}					t_env;

typedef struct		s_seg
{
	double			x_0;
	double			x_1;
	double			y_0;
	double			y_1;
	double			d_x;
	double			d_y;
}					t_sgmt;

void	print_map(t_coord **map, t_env *env);



void				fdf_error(char *message);
char				*get_map(char *filename);

t_coord				**parse(char **str, t_env *env);
void				check_map(char *str, int *x_max, int *y_max);



#endif