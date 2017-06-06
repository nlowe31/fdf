/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:26:02 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:42:45 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isdigit_base(int s, int base)
{
	int c;

	c = ft_tolower(s);
	if (base <= 10)
		return (ft_isdigit(c));
	return (ft_isdigit(c) || (ft_isalpha(c) && (c - 'a') < (base - 10)));
}
