/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:55:27 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_precision(t_data *data)
{
	int	precision;

	precision = data->precision;
	if (precision > 0)
		while (--precision >= 0)
			fill_buff_c(data, '0');
	return (0);
}

int	f_zero(t_data *data)
{
	int	zero;
	int	precision;

	precision = (data->precision > 0) ? data->precision : 0;
	zero = (int)(data->width - (data->len + precision + data->sign));
	if (zero > 0)
		while (--zero >= 0)
			fill_buff_c(data, '0');
	return (0);
}

int	f_width(t_data *data)
{
	int	width;
	int	precision;

	precision = (data->precision > 0) ? (int)data->precision : 0;
	width = (int)(data->width - (data->len + precision + data->sign));
	if (width > 0)
		while (--width >= 0)
			fill_buff_c(data, ' ');
	return (0);
}
