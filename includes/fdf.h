/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:33:02 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/26 16:49:24 by nlowe            ###   ########.fr       */
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

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

typedef struct		s_env
{
	void			*mlx_ptr;
	void			*win;
	t_coord			**map;
	int				x_max;
	int				y_max;
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


#endif