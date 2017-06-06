/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:42:13 by nlowe             #+#    #+#             */
/*   Updated: 2017/06/06 14:52:30 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	refresh(t_env *env, void (*f)(t_env *, int, int))
{
	int		y;
	int		x;

	mlx_destroy_image(env->core, env->img);
	env->img = mlx_new_image(env->core, IMG_WIDTH, IMG_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp),
		&(env->ls), &(env->en));
	y = 0;
	while (y < env->y_max)
	{
		x = 0;
		while (x < env->x_max)
		{
			f(env, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->core, env->win, env->img, 0, 0);
}

void	killswitch(t_env *env)
{
	mlx_destroy_image(env->core, env->img);
	mlx_destroy_window(env->core, env->win);
	free(env);
	exit(1);
}

int		keyhook(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == 53)
		killswitch(env);
	if (keycode == 24 || keycode == 27)
	{
		XS += (keycode == 24 ? 1 : -1);
		YS += (keycode == 24 ? 1 : -1);
		ZS += (keycode == 24 ? 1 : -1);
	}
	if (keycode == 123 || keycode == 124)
		XM += (keycode == 123 ? 10 : -10);
	if (keycode == 125 || keycode == 126)
		YM += (keycode == 126 ? 10 : -10);
	if (keycode == 116 || keycode == 121)
		ZS += (keycode == 121 ? -1 : 1);
	if (keycode == 18 || keycode == 19)
		env->projection = (keycode == 18 ? isometric : parallel);
	refresh(env, add_to_image);
	return (1);
}

void	fdf(t_env *env)
{
	env->core = mlx_init();
	env->win = mlx_new_window(env->core, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->core, IMG_WIDTH, IMG_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp),
		&(env->ls), &(env->en));
	mlx_hook(env->win, 2, 3, keyhook, env);
	refresh(env, add_to_image);
	mlx_loop(env->core);
}
