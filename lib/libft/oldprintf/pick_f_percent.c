/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:09:15 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pick_f_percent(t_data *data)
{
	data->len = 1;
	data->precision = 0;
	if (data->flags[MINUS])
	{
		fill_buff_c(data, '%');
		f_width(data);
	}
	else if (data->flags[ZERO])
	{
		f_zero(data);
		fill_buff_c(data, '%');
	}
	else if (data->width > 0)
	{
		f_width(data);
		fill_buff_c(data, '%');
	}
	else
		fill_buff_c(data, '%');
	return (0);
}
