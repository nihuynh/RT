/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:23:49 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 22:05:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include <stdio.h>

void	test1(void)
{
	ft_printf("Just a string\n");
	ft_printf("%s\n", "Just a string arg");
	ft_printf("Enterlace %s\n", "string");
	ft_printf("%d\n", 5000);
	ft_printf("Enterlace %d\n", 5000);
	ft_printf("%f\n", 3.14);
	ft_printf("Enterlace %f\n", 3.14);
}

void	test_float(void)
{
	float		f;
	double		d;
	long double	ld;

	f = 3.14;
	d = 3.14;
	ld = 3.14;
	printf("float %f double %lf ldouble %Lf\n", f, d, ld);
	ft_printf("ft = float %f double %lf ldouble %Lf\n", f, d, ld);
}

void	test_pointer(void)
{
	int	pistache;

	pistache = 69;
	printf("pointer %p\n", (void*)&pistache);
	ft_printf("pointer %p\n", &pistache);
}

int		main(void)
{
	test1();
	test_float();
	test_pointer();
	return (0);
}
