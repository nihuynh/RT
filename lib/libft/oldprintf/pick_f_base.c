/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:33:50 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <stdlib.h>

static int	f_x_sharp(t_data *data, const char *ptr)
{
	if (data->flags[SHARP] > 0 && *ptr == 'x')
		print_str("0x", data, "z");
	else if (data->flags[SHARP] && *ptr == 'X')
		print_str("0X", data, "z");
	else if (data->flags[SHARP] && (*ptr == 'o' || *ptr == 'O'))
		print_str("0", data, "z");
	return (0);
}

static char	*determine_xo_call_two(const char *ptr, uintmax_t tmp)
{
	if (*ptr == 'x')
		return (to_base(tmp, BASE_H));
	else if (*ptr == 'X')
		return (to_base(tmp, BASE_HC));
	else if (*ptr == 'o' || *ptr == 'O')
		return (to_base(tmp, BASE_O));
	else
		return (NULL);
}

static char	*determine_xo_call(const char *ptr, va_list param, t_data *data)
{
	uintmax_t	tmp;

	if (*ptr == 'O')
		tmp = va_arg(param, uintmax_t);
	else if (data->length[H] > 1)
		tmp = (unsigned char)va_arg(param, unsigned long);
	else if (data->length[H] == 1)
		tmp = (unsigned short)va_arg(param, unsigned long);
	else if (data->length[L] == 1)
		tmp = va_arg(param, unsigned long);
	else if (data->length[L] == 2)
		tmp = va_arg(param, unsigned long long);
	else if (data->length[J] == 1)
		tmp = va_arg(param, uintmax_t);
	else if (data->length[Z] == 1)
		tmp = va_arg(param, size_t);
	else if (*ptr == 'x' || *ptr == 'X' || *ptr == 'o')
	{
		tmp = va_arg(param, unsigned int);
		if (tmp > 4294967295)
			tmp = (4294967296 - tmp) * -1;
	}
	else
		tmp = va_arg(param, uintmax_t);
	return (determine_xo_call_two(ptr, tmp));
}

static int	pick_f_x_two(char *result, t_data *data, const char *ptr)
{
	if (data->precision > 0)
	{
		f_width(data);
		f_x_sharp(data, ptr);
		f_precision(data);
		print_str(result, data, "z");
	}
	else if (data->flags[ZERO])
	{
		f_x_sharp(data, ptr);
		f_zero(data);
		print_str(result, data, "z");
	}
	else if (data->width > 0)
	{
		f_width(data);
		f_x_sharp(data, ptr);
		print_str(result, data, "z");
	}
	else
	{
		f_x_sharp(data, ptr);
		print_str(result, data, "z");
	}
	return (0);
}

int			pick_f_base(va_list param, t_data *data, const char *ptr)
{
	char	*result;

	result = determine_xo_call(ptr, param, data);
	data->len = (result != NULL) ? ft_strlen(result) : 0;
	data->flags[ZERO] = (data->precision == 0) ? data->flags[ZERO] : 0;
	if (data->len == 1 && *result == '0')
		return (exception_zero_x(data, ptr));
	data->width = (data->flags[SHARP] && (*ptr == 'x' || *ptr == 'X')) ?
		data->width - 2 : data->width;
	data->len = (data->flags[SHARP] && (*ptr == 'o' || *ptr == 'O')) ?
		++data->len : data->len;
	if (data->precision >= 0)
		data->precision = (data->precision > data->len) ?
			data->precision - data->len : 0;
	if (data->flags[MINUS])
	{
		f_x_sharp(data, ptr);
		f_precision(data);
		print_str(result, data, "z");
		f_width(data);
	}
	else
		(pick_f_x_two(result, data, ptr));
	free(result);
	return (0);
}
