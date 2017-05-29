/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:45:37 by nlowe             #+#    #+#             */
/*   Updated: 2017/05/29 15:52:44 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main(int ac, char **av)
{
	int		test;

	(void)ac;
	ft_printf("in base: %d\n", ft_isdigit_base(av[1][0], 16));
	test = ft_atoi_base(av[1], 16);
	ft_printf("result: %d\n", test);
	return (0);
}