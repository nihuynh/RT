/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_u_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:33:48 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"

static void			ft_put_u(uintmax_t nb, t_data *data)
{
	if (nb / 10)
		ft_put_u(nb / 10, data);
	fill_buff_c(data, nb % 10 + 48);
}

uintmax_t			len_u(uintmax_t nb)
{
	uintmax_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb >= 1)
	{
		nb = nb / 10;
		++len;
	}
	return (len);
}

static uintmax_t	retrieve_u_param(t_data *data, va_list param)
{
	if (data->length[L] == 1)
		return (va_arg(param, unsigned long));
	else if (data->length[L] == 2)
		return (va_arg(param, unsigned long long));
	else if (data->length[H] == 1)
		return ((unsigned short)va_arg(param, unsigned long));
	else if (data->length[H] == 2)
		return ((unsigned char)va_arg(param, unsigned long));
	else if (data->length[J] == 1)
		return (va_arg(param, uintmax_t));
	else if (data->length[Z] == 1)
		return (va_arg(param, size_t));
	return (va_arg(param, unsigned int));
}

static int			pick_f_u_2(t_data *data, uintmax_t nb, int prec)
{
	if (data->precision > 0)
	{
		f_width(data);
		f_precision(data);
	}
	else if (data->flags[ZERO])
	{
		if (prec <= 0)
			f_zero(data);
		else
			f_width(data);
	}
	else if (data->width > 0)
		f_width(data);
	ft_put_u(nb, data);
	return (0);
}

int					pick_f_u(va_list param, t_data *data)
{
	uintmax_t	nb;
	int			prec;

	nb = retrieve_u_param(data, param);
	data->len = len_u(nb);
	data->flags[ZERO] = (data->precision == 0) ? data->flags[ZERO] : 0;
	if (data->len == 1 && nb == 0)
		return (exception_zero_u(data));
	prec = data->precision;
	data->precision = (data->precision > data->len) ?
		data->precision - data->len : 0;
	if (data->flags[MINUS])
	{
		f_precision(data);
		ft_put_u(nb, data);
		return (f_width(data));
	}
	return (pick_f_u_2(data, nb, prec));
}
