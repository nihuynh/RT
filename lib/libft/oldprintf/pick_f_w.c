/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_w.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:09:32 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <stdlib.h>

static void	write_quadruple(wchar_t unicode, t_data *data)
{
	char *str;

	if (!(str = ft_strnew(4)))
		return ;
	str[0] = (char)(unicode >> 18) + 0xf0;
	str[1] = (char)(unicode >> 12 & 0x3f) + 0x80;
	str[2] = (char)(unicode >> 6 & 0x3f) + 0x80;
	str[3] = (char)(unicode & 0x3f) + 0x80;
	fill_buff_c(data, str[0]);
	fill_buff_c(data, str[1]);
	fill_buff_c(data, str[2]);
	fill_buff_c(data, str[3]);
	ft_strdel(&str);
}

static void	write_triple(wchar_t unicode, t_data *data)
{
	char *str;

	if (!(str = ft_strnew(3)))
		return ;
	str[0] = (char)(unicode >> 12) + 0xe0;
	str[1] = (char)(unicode >> 6 & 0x3f) + 0x80;
	str[2] = (char)(unicode & 0x3f) + 0x80;
	fill_buff_c(data, str[0]);
	fill_buff_c(data, str[1]);
	fill_buff_c(data, str[2]);
	ft_strdel(&str);
}

static void	write_double(wchar_t unicode, t_data *data)
{
	char *str;

	if (!(str = ft_strnew(2)))
		return ;
	str[0] = (char)(unicode >> 6) + 0xc0;
	str[1] = (char)(unicode & 0x3f) + 0x80;
	fill_buff_c(data, str[0]);
	fill_buff_c(data, str[1]);
	ft_strdel(&str);
}

int			write_w(t_data *data, wchar_t unicode)
{
	if (unicode < 129)
		fill_buff_c(data, (char)unicode);
	else if (unicode < 2049)
		write_double(unicode, data);
	else if (unicode < 65536)
		write_triple(unicode, data);
	else if (unicode < 2097152)
		write_quadruple(unicode, data);
	return (0);
}

int			pick_f_w(t_data *data, va_list param)
{
	wchar_t unicode;

	if ((unicode = va_arg(param, wchar_t)) < 0 || unicode > 2097152)
		return (data->ret_val = -1);
	determine_w_len(data, unicode);
	if (data->flags[MINUS] == 0 && data->width > 0)
		f_width(data);
	if (MB_CUR_MAX == 1 && unicode <= 255)
		fill_buff_c(data, unicode);
	else if (MB_CUR_MAX == 1 || unicode > 1114111 || unicode < 0 ||
			(unicode >= 55295 && unicode <= 57343))
		data->ret_val = -1;
	else
		write_w(data, unicode);
	if (data->flags[MINUS] > 0)
	{
		f_width(data);
		return (-1);
	}
	return (0);
}
