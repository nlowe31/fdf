/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:33:02 by nlowe             #+#    #+#             */
/*   Updated: 2017/02/19 00:38:07 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"

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

#endif
