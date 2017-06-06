/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:53:14 by nlowe             #+#    #+#             */
/*   Updated: 2017/06/06 15:14:20 by nlowe            ###   ########.fr       */
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

int		check_filename(char *filename)
{
	char	*extension;

	if (!(extension = ft_strrchr(filename, '.')))
		return (0);
	if (ft_strcmp(extension, ".fdf") == 0)
		return (1);
	return (0);
}

void	get_scale(t_env *env)
{
	int		scale;

	if (!env->x_max || !env->y_max)
		scale = 1;
	else if ((scale = (int)IMG_HEIGHT / env->y_max) >
		((int)IMG_WIDTH / env->x_max))
		scale = (int)IMG_WIDTH / env->x_max;
	scale /= 3;
	env->x_scale = scale;
	env->y_scale = scale;
	env->z_scale = 1;
}

void	print_instructions(void)
{
	ft_printf(" ----------------------------- \n\
|                             |\n\
|            FdF              |\n\
|           nlowe             |\n\
|                             |\n\
|                             |\n\
|          CONTROLS           |\n\
|                             |\n\
|           + -   Zoom        |\n\
|  Page Up/Down   Map Depth   |\n\
|    Arrow Keys   Pan         |\n\
|           Esc   Exit        |\n\
|                             |\n ----------------------------- \n");
}

int		main(int ac, char **av)
{
	t_env	*env;
	char	*map;

	if (ac != 2)
		fdf_error("invalid argument");
	if (!(check_filename(av[1])))
		fdf_error("invalid file type");
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		fdf_error(0);
	ft_int_init(6, &(env->x_max), &(env->y_max), &(XM), &(YM), &(XS), &(YS));
	env->projection = isometric;
	if (!(map = get_map(av[1])))
		fdf_error("invalid file");
	check_map(map, &(env->x_max), &(env->y_max));
	env->map = parse(&map, env);
	get_scale(env);
	XM = (IMG_WIDTH / 2) - (env->x_max / 2);
	YM = (IMG_HEIGHT / 2) - (env->y_max / 2);
	print_instructions();
	fdf(env);
	return (0);
}
