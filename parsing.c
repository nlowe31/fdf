/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:42:32 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/25 18:59:06 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char		*get_map(char *filename)
{
	int		fd;
	char	*map;
	char	*trash;
	char	*buff;

	if ((fd = open(filename, O_RDONLY)) < 0)
		fdf_error(1, 0);
	if (!(line = ft_strnew(0)))
		fdf_error(1, 0);
	while (get_next_line(fd, &buff) > 0)
	{
		trash = buff;
		if (!(map = ft_strjoin(map, buff)))
			fdf_error(1, 0);
		ft_strdel(&trash);
		trash = map;
		if (!(map = ft_strjoin(map, "\n")))
			fdf_error(1, 0);
		ft_strdel(&map);
	}
	ft_strdel(&buff);
	return (map);
}