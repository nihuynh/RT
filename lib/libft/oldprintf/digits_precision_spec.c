/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_precision_spec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:55:44 by sklepper          #+#    #+#             */
/*   Updated: 2018/09/27 15:14:52 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_zero_s(t_data *data)
{
	int	zero;

	zero = (int)(data->width - data->len);
	if (zero > 0)
		while (--zero >= 0)
			fill_buff_c(data, '0');
	return (0);
}

int	f_width_s(t_data *data)
{
	int	width;

	width = (int)(data->width - data->len);
	if (width > 0)
		while (--width >= 0)
			fill_buff_c(data, ' ');
	return (0);
}

int	f_width_p(t_data *data, uintptr_t nb)
{
	int	width;

	width = (int)(data->width - data->len);
	if (nb == 0)
		width--;
	if (width > 0)
		while (--width >= 0)
			fill_buff_c(data, ' ');
	return (0);
}
