/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prec1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 15:28:28 by modaouch          #+#    #+#             */
/*   Updated: 2018/12/09 18:05:28 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftio.h"

void	ft_space(va_list ap, t_arg *stk)
{
	int i;

	i = 0;
	stk->space = va_arg(ap, int);
	while (i++ < stk->space)
		ft_putchar(' ');
	stk->i++;
}
