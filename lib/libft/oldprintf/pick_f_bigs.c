/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_bigs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:47 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static void		determine_lengths(t_data *data, int *len, int i, wchar_t *str)
{
	if (str[i] < 129 || (str[i] <= 255 && MB_CUR_MAX == 1))
	{
		--*len;
		data->len += (*len >= 0) ? 1 : 0;
	}
	else if (str[i] < 2049)
	{
		*len -= 2;
		data->len += (*len >= 0) ? 2 : 0;
	}
	else if (str[i] < 65536)
	{
		*len -= 3;
		data->len += (*len >= 0) ? 3 : 0;
	}
	else if (str[i] < 2097152)
	{
		*len -= 4;
		data->len += (*len >= 0) ? 4 : 0;
	}
}

static void		determine_ws_len(t_data *data, wchar_t *str)
{
	int	len;
	int	i;

	i = -1;
	len = data->precision;
	data->len = 0;
	while (str[++i] && len > 0)
		determine_lengths(data, &len, i, str);
}

static void		write_bigs_2(t_data *data, wchar_t *str, int i)
{
	if (MB_CUR_MAX == 1 && str[i] <= 255)
		fill_buff_c(data, str[i]);
	else if (MB_CUR_MAX == 1 || str[i] > 1114111 || str[i] < 0 ||
			(str[i] >= 55295 && str[i] <= 57343))
		data->ret_val = -1;
	else
		write_w(data, str[i]);
}

static void		write_bigs(t_data *data, wchar_t *str)
{
	int	i;
	int	len;

	i = -1;
	len = (data->precision > 0) ? data->precision : data->len;
	while (str[++i] && len > 0)
	{
		if (data->precision > 0)
		{
			if (str[i] < 129 || (str[i] <= 255 && MB_CUR_MAX == 1))
				--len;
			else if (str[i] < 2049)
				len -= 2;
			else
				len -= (str[i] >= 2049 && str[i] < 65536) ? 3 : 4;
		}
		if (len >= 0)
			write_bigs_2(data, str, i);
	}
}

int				pick_f_bigs(va_list param, t_data *data)
{
	wchar_t *str;
	int		i;

	i = -1;
	if (!(str = va_arg(param, wchar_t *)))
		return (exception_bigs(data, "(null)"));
	while (str[++i])
		determine_w_len(data, str[i]);
	if (data->precision > 0)
		determine_ws_len(data, str);
	data->len = (data->precision < 0) ? 0 : data->len;
	if (data->flags[MINUS])
	{
		write_bigs(data, str);
		return (f_width_s(data));
	}
	else if (data->flags[ZERO])
		f_zero_s(data);
	else
		f_width_s(data);
	write_bigs(data, str);
	return (0);
}
