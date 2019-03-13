/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:31:09 by modaouch          #+#    #+#             */
/*   Updated: 2018/12/09 20:20:34 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "ft_printf.h"
#include "ftio.h"
#include "ftstring.h"
#include "ftconvert.h"

void	ft_string(va_list ap, t_arg *stk)
{
	ft_putstr(va_arg(ap, char *));
	stk->i++;
}

void	ft_char(va_list ap, t_arg *stk)
{
	ft_putchar(va_arg(ap, int));
	stk->i++;
}

void	ft_double(va_list ap, t_arg *stk)
{
	stk->conv = ft_dtoa(va_arg(ap, double), 6);
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i++;
}

void	ft_pointer(va_list ap, t_arg *stk)
{
	stk->conv = ft_lltoa_base((long long)va_arg(ap, uintptr_t), 16);
	ft_putstr("0x");
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i++;
}
