/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 01:07:15 by modaouch          #+#    #+#             */
/*   Updated: 2018/12/09 20:47:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONV_H
# define FT_CONV_H

# include "ft_printf.h"

t_conv g_convtab[] =
{
	{"c", &ft_char},
	{"s", &ft_string},
	{"p", &ft_pointer},
	{"d", &ft_digit},
	{"D", &ft_digit},
	{"i", &ft_digit},
	{"o", &ft_octal},
	{"x", &ft_hex},
	{"X", &ft_hex_up},
	{"f", &ft_double},
	{"%", &ft_percent},
	{0, NULL}
};

#endif
