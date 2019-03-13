/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:14:05 by flonger           #+#    #+#             */
/*   Updated: 2018/12/04 02:37:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include <string.h>

static void	ft_dec_hexa(size_t n, size_t digit)
{
	char *base;

	base = "0123456789abcdef";
	if (digit == 0)
		return ;
	ft_dec_hexa(n / 16, digit - 1);
	ft_putchar(base[n % 16]);
}

static void	ft_print_val_hexa(char *str, size_t index, size_t size)
{
	size_t i;

	i = 0;
	while (i < 16 && i + index < size)
	{
		ft_dec_hexa(str[i + index], 2);
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
	while (i < 16)
	{
		ft_putchar(' ');
		ft_putchar(' ');
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
}

static void	ft_print_val_dec(char *str, size_t index, size_t size)
{
	size_t i;

	i = 0;
	while (i < 16 && i + index < size)
	{
		if (str[i + index] <= 31 || str[i + index] == 127)
			ft_putchar('.');
		else
			ft_putchar(str[i + index]);
		i++;
	}
}

void		*ft_print_memory(void *addr, size_t size)
{
	size_t	i;
	char	*str;
	int		nbl;

	if (size == 0)
		return (addr);
	str = addr;
	i = 0;
	nbl = (size % 16 == 0) ? 0 : 1;
	while (i < size / 16 + nbl)
	{
		ft_dec_hexa(i * 16, 8);
		ft_putchar(':');
		ft_putchar(' ');
		ft_print_val_hexa(str, i * 16, size);
		ft_print_val_dec(str, i * 16, size);
		ft_putchar('\n');
		i++;
	}
	return (addr);
}
