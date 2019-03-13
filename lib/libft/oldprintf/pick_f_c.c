/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:08:58 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <stdlib.h>

int	pick_f_c(va_list param, t_data *data, char ptr)
{
	char	result;

	if (ptr == 'c')
		result = va_arg(param, int);
	else if (ptr == '\0')
		return (0);
	else
		result = ptr;
	data->len = 1;
	data->precision = 0;
	if (data->flags[MINUS])
	{
		fill_buff_c(data, result);
		return (f_width(data));
	}
	else if (data->flags[ZERO])
		f_zero(data);
	else if (data->width)
		f_width(data);
	return (fill_buff_c(data, result));
}
