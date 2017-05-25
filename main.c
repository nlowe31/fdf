/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:53:14 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/25 18:53:04 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_error(int exit, int arnaud)
{
	if (arnaud)
		ft_dprintf(2, "fdf: %s\n", strerror(arnaud));
	else
		perror("fdf");
	if (exit)
		exit(0);
	return (1);
}

int		main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "MLX Test");
	mlx_loop(mlx);
}
