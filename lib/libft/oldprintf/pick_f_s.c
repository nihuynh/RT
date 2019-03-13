/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:08:46 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"

static int	exception_s(t_data *data)
{
	data->len = (data->precision < 0) ? 0 : 6;
	data->len = (data->precision > 0 && data->precision < data->len) ?
		data->precision : data->len;
	data->precision = 0;
	if (data->flags[MINUS])
	{
		write_str(data, "(null)");
		return (f_width_s(data));
	}
	else if (data->flags[ZERO])
		f_zero(data);
	else if (data->width > 0)
		f_width_s(data);
	write_str(data, "(null)");
	return (0);
}

static int	pick_f_s_2(char *str, t_data *data)
{
	int	i;

	i = -1;
	if (data->width > 0)
	{
		f_width_s(data);
		write_str(data, str);
	}
	else
		write_str(data, str);
	return (0);
}

int			pick_f_s(va_list param, t_data *data)
{
	char	*str;
	int		i;

	i = -1;
	str = va_arg(param, char*);
	if (!str)
		return (exception_s(data));
	data->len = (data->precision < 0) ? 0 : ft_strlen(str);
	data->len = (data->precision > 0 && data->precision < data->len) ?
		data->precision : data->len;
	data->precision = 0;
	if (data->flags[MINUS])
	{
		write_str(data, str);
		f_width_s(data);
	}
	else if (data->flags[ZERO])
	{
		f_zero(data);
		write_str(data, str);
	}
	else
		pick_f_s_2(str, data);
	return (0);
}
