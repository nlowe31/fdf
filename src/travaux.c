/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   travaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:41:05 by nlowe             #+#    #+#             */
/*   Updated: 2017/06/06 13:47:53 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			ft_printf("(%d, %d, %d; %x) ", map[y][x].x, map[y][x].y, map[y][x].z, map[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

// int		old_main(int ac, char **av)
// {
// 	t_env	*env;
// 	char	*map;

// 	if (ac != 2)
// 		fdf_error("invalid argument");
// 	if (!(check_filename(av[1])))
// 		fdf_error("invalid file type");
// 	if (!(env = (t_env *)malloc(sizeof(t_env))))
// 		fdf_error(0);
// 	ft_int_init(6, &(env->x_max), &(env->y_max), &(XM), &(YM), &(XS), &(YS));
// 	env->projection = isometric;
// 	ft_printf("%d, %d\n", env->x_max, env->y_max);
// 	map = get_map(av[1]);
// 	check_map(map, &(env->x_max), &(env->y_max));
// 	ft_printf("%d, %d\n", env->x_max, env->y_max);
// 	ft_printf("map\n---\n%s---\n", map);
// 	env->map = parse(&map, env);
// 	ft_printf("%d, %d\n", env->x_max, env->y_max);
// 	XS = 1;
// 	YS = 1;
// 	ft_printf("%d, %d\n", env->x_max, env->y_max);
// 	ft_printf("x_scale: %d y_scale: %d", XS, YS);
// 	ZS = 1;
// 	XM = (IMG_WIDTH / 2) - (env->x_max / 2);
// 	YM = (IMG_HEIGHT / 2) - (env->y_max / 2);
// 	ft_printf("%d%d\n", env->x_max, env->y_max);
// 	print_map(env->map, env);
// 	fdf(env);
// 	return (0);
// }
