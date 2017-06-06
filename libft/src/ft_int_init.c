/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:35:26 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:52:03 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_int_init(const int count, ...)
{
	va_list		args;
	int			i;
	int			*ptr;

	i = 0;
	va_start(args, count);
	while (i < count)
	{
		ptr = va_arg(args, int *);
		*ptr = 0;
		i++;
	}
	va_end(args);
}
