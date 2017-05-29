/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:53:14 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:11:13 by nlowe            ###   ########.fr       */
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

void	put_pixel(t_env *env, int x, int y, int color)
{
	int		pos;
	int		i;

	if (x > IMG_WIDTH || y > IMG_HEIGHT || x < 0 || y < 0)
		return ;
	pos = (y * env->ls) + (x * env->bpp);
	i = 0;
	while (i < env->bpp)
	{
		env->data[pos + i] = (color >> (8 * i)) & 0xff;
		i++;
	}
}

int		keyhook(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_image(((t_env *)param)->core, ((t_env *)param)->img);
		mlx_destroy_window(((t_env *)param)->core, ((t_env *)param)->win);
		free(param);
		exit(1);
	}
	ft_printf("key: %d\n", keycode);
	(void)param;
	return (1);
}

void	fdf(t_env *env)
{
	env->core = mlx_init();
	env->win = mlx_new_window(env->core, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->core, IMG_WIDTH, IMG_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp), &(env->ls), &(env->en));
	mlx_key_hook(env->win, keyhook, env);
	mlx_loop(env->core);
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
	check_map(map, &(env->x_max), &(env->y_max));
	ft_printf("%d%d\n", env->x_max, env->y_max);	
	ft_printf("map\n---\n%s", map);
	env->map = parse(&map, env);
	ft_printf("%d%d\n", env->x_max, env->y_max);
	print_map(env->map, env);
	fdf(env);
	// mlx = mlx_init();
	// win = mlx_new_window(mlx, 400, 400, "MLX Test");
	// mlx_loop(mlx);
}
