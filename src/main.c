/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:53:14 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/26 16:49:52 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error(char *message)
{
	if (message)
		ft_dprintf(2, "FdF: %s\n", message);
	else
		perror("FdF");
	exit(0);
}

void	print_map(t_coord **map, t_env *env)
{
	int		x;
	int		y;

	y = 0;
	while (y < env->y_max)
	{
		x = 0;
		while (x < env->x_max)
		{
			ft_printf("(%d, %d, %d) ", map[y][x].x, map[y][x].y, map[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int		main(int ac, char **av)
{
	t_env	*env;
	char	*map;

	if (ac != 2)
		fdf_error("invalid argument");
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		fdf_error(0);
	ft_int_init(2, &(env->x_max), &(env->y_max));
	ft_printf("%d%d\n", env->x_max, env->y_max);
	map = get_map(av[1]);
	// ft_printf("map\n---\n%s", map);
	env->map = parse(&map, env);
	ft_printf("%d%d\n", env->x_max, env->y_max);
	print_map(env->map, env);
	// mlx = mlx_init();
	// win = mlx_new_window(mlx, 400, 400, "MLX Test");
	// mlx_loop(mlx);
}
