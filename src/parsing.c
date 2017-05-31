/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:42:32 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/31 16:34:55 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		check_column(int *x, int *x_max, int *y_max)
{
	if (!(*x_max))
		*x_max = *x;
	else if (*x != *x_max)
		fdf_error("invalid map");
	*x = 0;
	(*y_max)++;
}

void		check_map(char *str, int *x_max, int *y_max)
{
	int		pos;
	int		x;

	pos = 0;
	x = 0;
	while (str[pos])
	{
		while (str[pos] == ' ' || str[pos] == '\t')
			pos++;
		if (ft_isdigit(str[pos]) || (str[pos] == '-' && ft_isdigit(str[pos + 1])))
			x++;
		while (ft_isdigit(str[pos]) || (str[pos] == '-' && ft_isdigit(str[pos + 1])))
			pos++;
		if (str[pos] == ',')
			pos++;
		if (!ft_isdigit(str[pos]) && !ft_isspace(str[pos]))
			fdf_error("invalid map");
		if (str[pos++] == '\n')
			check_column(&x, x_max, y_max);
	}
}

void		get_color(t_coord **map, char **str, int *x, int *y)
{
	if (**str == '0')
		(*str)++;
	if (**str == 'x')
		(*str)++;
	map[*y][*x].color = ft_atoi_base(*str, 16);
	while (ft_isdigit_base(**str, 16))
		(*str)++;
}

void		get_coord(t_coord **map, char **str, int *x, int *y)
{
	while (ft_isspace(**str))
		(*str)++;
	if (ft_isdigit(**str) || **str == '-')
		(map[*y][*x]).z = ft_atoi(*str);
	(map[*y][*x]).x = *x;
	(map[*y][*x]).y = *y;
	while (ft_isdigit(**str) || **str == '-')
		(*str)++;
	if (**str == ',')
	{
		(*str)++;
		get_color(map, str, x, y);
	}
	else
		map[*y][*x].color = 0xffffff;
	(*x)++;
}

t_coord		**parse(char **str, t_env *env)
{
	t_coord		**map;
	int			x;
	int			y;

	y = 0;
	if (!(map = (t_coord **)malloc(sizeof(t_coord *) * (env->y_max + 1))))
		fdf_error(0);
	while (y < env->y_max)
	{
		if (!(map[y] = (t_coord *)malloc(sizeof(t_coord) * (env->x_max + 1))))
			fdf_error(0);
		x = 0;
		while (x < env->x_max)
			get_coord(map, str, &x, &y);
		y++;
	}
	return (map);
}

char		*get_map(char *filename)
{
	int		fd;
	char	*map;
	char	*trash;
	char	*buff;

	if ((fd = open(filename, O_RDWR)) <= 0)
		fdf_error(0);
	if (!(buff = ft_strnew(0)))
		fdf_error(0);
	map = NULL;
	while (get_next_line(fd, &buff) > 0)
	{
		trash = buff;
		if (!(map = ft_strjoin(map, buff)))
			fdf_error(0);
		ft_strdel(&trash);
		trash = map;
		if (!(map = ft_strjoin(map, "\n")))
			fdf_error(0);
		ft_strdel(&trash);
	}
	ft_strdel(&buff);
	return (map);
}
