/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:53:46 by nlowe             #+#    #+#             */
/*   Updated: 2017/06/06 15:02:39 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		check_column(int *x, int *x_max, int *y_max)
{
	if (!(*x_max))
		*x_max = *x;
	else if (*x != *x_max)
		fdf_error("invalid map: invalid map size");
	*x = 0;
	(*y_max)++;
}

void		check_color(char *str, int *pos)
{
	int		digits;

	digits = 0;
	if (str[*pos] == ',')
		(*pos)++;
	if (str[*pos] == '0')
		(*pos)++;
	if (str[*pos] == 'x')
		(*pos)++;
	while (ft_isdigit_base(str[*pos], 16))
	{
		digits++;
		(*pos)++;
	}
	if (digits != 6)
		fdf_error("invalid map: invalid color specified");
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
		if (ft_isdigit(str[pos]) || (str[pos] == '-' &&
			ft_isdigit(str[pos + 1])))
			x++;
		while (ft_isdigit(str[pos]) || (str[pos] == '-' &&
			ft_isdigit(str[pos + 1])))
			pos++;
		if (str[pos] == ',')
			check_color(str, &pos);
		if (!ft_isdigit(str[pos]) && !ft_isspace(str[pos]))
			fdf_error("invalid map: invalid data point");
		if (str[pos++] == '\n')
			check_column(&x, x_max, y_max);
	}
}
