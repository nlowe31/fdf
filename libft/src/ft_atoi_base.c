/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:27:04 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:49:55 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_base(const char *s, int base)
{
	int		result;
	int		sign;
	char	*str;

	str = (char *)s;
	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' && (ft_isdigit(*(str + 1))))
		str++;
	if (*str == '-' && (ft_isdigit(*(str + 1))))
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit_base(*str, base))
	{
		if (ft_isdigit(*str))
			result = (result * base) + (*str - '0');
		else
			result = (result * base) + (ft_tolower(*str) - 'a' + 10);
		str++;
	}
	return (sign * result);
}
