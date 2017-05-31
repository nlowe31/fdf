/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:53:14 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/31 19:27:31 by nlowe            ###   ########.fr       */
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
	pos = (y * env->ls) + (x * 4);
	i = 0;
	while (i < 3)
	{
		env->data[pos + i] = (color >> (8 * i)) & 0xff;
		i++;
	}
}

t_seg	isometric(t_env *env, int x, int y, int direction)
{
	t_seg	ret;

	if (direction == 1)
	{
		ret.x_0 = (env->map[y][x].x * env->x_scale) - (env->map[y][x].y * env->y_scale) + env->x_move;
		ret.y_0 = (((env->map[y][x].x * env->x_scale) + (env->map[y][x].y * env->y_scale)) / 2) - (env->map[y][x].z * env->z_scale) + env->y_move;
		ret.x_1 = (env->map[y + 1][x].x * env->x_scale) - (env->map[y + 1][x].y * env->y_scale) + env->x_move;
		ret.y_1 = (((env->map[y + 1][x].x * env->x_scale) + (env->map[y + 1][x].y * env->y_scale)) / 2) - (env->map[y + 1][x].z * env->z_scale) + env->y_move;
	}
	else
	{
		ret.x_0 = (env->map[y][x].x * env->x_scale) - (env->map[y][x].y * env->y_scale) + env->x_move;
		ret.y_0 = (((env->map[y][x].x * env->x_scale) + (env->map[y][x].y * env->y_scale)) / 2) - (env->map[y][x].z * env->z_scale) + env->y_move;
		ret.x_1 = (env->map[y][x + 1].x * env->x_scale) - (env->map[y][x + 1].y * env->y_scale) + env->x_move;
		ret.y_1 = (((env->map[y][x + 1].x * env->x_scale) + (env->map[y][x + 1].y * env->y_scale)) / 2) - (env->map[y][x + 1].z * env->z_scale) + env->y_move;
	}
	return (ret);
}

void	put_segment(t_env *env, t_seg seg, int color)
{
	seg.d_x = abs(seg.x_1 - seg.x_0);
	seg.d_y = abs(seg.y_1 - seg.y_0);
	seg.s_x = (seg.x_0 < seg.x_1 ? 1 : -1);
	seg.s_y = (seg.y_0 < seg.y_1 ? 1 : -1);
	seg.err1 = (seg.d_x > seg.d_y ? seg.d_x : -seg.d_y) / 2;
	while (1)
	{
		put_pixel(env, seg.x_0, seg.y_0, color);
		if (seg.x_0 == seg.x_1 && seg.y_0 == seg.y_1)
			break ;
		seg.err2 = seg.err1;
		if (seg.err2 > -seg.d_x)
		{
			seg.err1 -= seg.d_y;
			seg.x_0 += seg.s_x;
		}
		if (seg.err2 < seg.d_y)
		{
			seg.err1 += seg.d_x;
			seg.y_0 += seg.s_y;
		}
	}
}

void	add_to_image(t_env *env, int x, int y)
{
	t_seg	seg;

	if (x + 1 < env->x_max)
	{
		seg = isometric(env, x, y, 0);
		put_segment(env, seg, 0xffffff);
	}
	if (y + 1 < env->y_max)
	{
		seg = isometric(env, x, y, 1);
		put_segment(env, seg, 0xffffff);
	}
}

void	refresh(t_env *env, void (*f)(t_env *, int, int))
{
	int		y;
	int		x;

	mlx_destroy_image(env->core, env->img);
	env->img = mlx_new_image(env->core, IMG_WIDTH, IMG_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp), &(env->ls), &(env->en));
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

int		keyhook(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_image(((t_env *)param)->core, ((t_env *)param)->img);
		mlx_destroy_window(((t_env *)param)->core, ((t_env *)param)->win);
		free(param);
		exit(1);
	}
	if (keycode == 24 || keycode == 27)
	{
		((t_env *)param)->x_scale += (keycode == 24 ? 1 : -1);
		((t_env *)param)->y_scale += (keycode == 24 ? 1 : -1);
	}
	if (keycode == 123 || keycode == 124)
		((t_env *)param)->x_move += (keycode == 123 ? -10 : 10);
	if (keycode == 125 || keycode == 126)
		((t_env *)param)->y_move += (keycode == 126 ? -10 : 10);
	if (keycode == 116 || keycode == 121)
		((t_env *)param)->z_scale += (keycode == 121 ? -1 : 1);
	ft_printf("key: %d\n", keycode);
	refresh((t_env *)param, add_to_image);
	return (1);
}

void	fdf(t_env *env)
{
	env->core = mlx_init();
	env->win = mlx_new_window(env->core, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->core, IMG_WIDTH, IMG_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &(env->bpp), &(env->ls), &(env->en));
	mlx_hook(env->win, 2, 3, keyhook, env);
	refresh(env, add_to_image);
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
	ft_int_init(4, &(env->x_max), &(env->y_max), &(env->x_move), &(env->y_move));
	env->x_scale = 10;
	env->y_scale = 10;
	env->z_scale = 10;
	ft_printf("%d%d\n", env->x_max, env->y_max);
	map = get_map(av[1]);
	check_map(map, &(env->x_max), &(env->y_max));
	ft_printf("%d%d\n", env->x_max, env->y_max);
	ft_printf("map\n---\n%s", map);
	env->map = parse(&map, env);
	ft_printf("%d%d\n", env->x_max, env->y_max);
	print_map(env->map, env);
	fdf(env);
}
