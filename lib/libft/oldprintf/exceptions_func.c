/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:52:57 by sklepper          #+#    #+#             */
/*   Updated: 2018/09/27 15:14:52 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	exception_zero_x(t_data *data, const char *ptr)
{
	data->len = 0;
	data->flags[SHARP] = (data->flags[ZERO] > 0) ? 0 : data->flags[SHARP];
	if (data->precision == 0 && data->width <= 1 && data->flags[SHARP] == 0)
		return (fill_buff_c(data, '0'));
	if (data->precision <= 0 && (*ptr == 'o' || *ptr == 'O'))
		data->precision = (data->flags[SHARP] > 0) ? 1 : -1;
	if (data->flags[MINUS] > 0)
	{
		f_precision(data);
		f_width(data);
		return (0);
	}
	else if (data->precision > 0)
	{
		f_width(data);
		f_precision(data);
	}
	else if (data->flags[ZERO])
		f_zero(data);
	else if (data->width > 0)
		f_width(data);
	else if (data->precision >= 0)
		return (fill_buff_c(data, '0'));
	return (1);
}

int	exception_bigs(t_data *data, char *str)
{
	int		i;
	int		len;

	i = -1;
	data->len = (data->precision > 0) ? data->precision : 6;
	data->len = (data->precision < 0) ? 0 : data->len;
	len = data->len;
	if (data->flags[MINUS])
	{
		while (str[++i] && --len >= 0)
			fill_buff_c(data, str[i]);
		return (f_width_s(data));
	}
	else if (data->flags[ZERO])
		f_zero_s(data);
	else if (data->width > 0)
		f_width_s(data);
	while (str[++i] && --len >= 0)
		fill_buff_c(data, str[i]);
	return (0);
}

int	exception_zero_u(t_data *data)
{
	data->len = 0;
	if (data->precision == 0 && data->width == 0)
		return (fill_buff_c(data, '0'));
	if (data->precision < 0)
	{
		f_width(data);
		return (0);
	}
	if (data->precision > 0)
	{
		f_width(data);
		f_precision(data);
	}
	else if (data->flags[ZERO])
		f_zero(data);
	else if (data->width > 0)
		f_width(data);
	else
		return (fill_buff_c(data, '0'));
	return (1);
}
