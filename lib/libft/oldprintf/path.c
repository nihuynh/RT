/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:05:48 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		path(char *ptr, va_list param, t_data *data)
{
	int i;

	i = 0;
	if ((i = flags(ptr, data)) > 0)
		return (i);
	else if ((i = length(ptr, data)) > 0)
		return (i);
	else if ((i = width(ptr, data)) > 0)
		return (i);
	else
		conversion(ptr, param, data);
	return (0);
}

int		width(char *ptr, t_data *data)
{
	if (*ptr == '.')
		return (precision(ptr + 1, data) + 1);
	else if (*ptr > '0' && *ptr <= '9')
		return (width_min(ptr, data));
	return (0);
}

int		flags(const char *ptr, t_data *data)
{
	if (*ptr == '#')
		return (flag_sharp(data));
	else if (*ptr == '0')
		return (flag_zero(data));
	else if (*ptr == '-')
		return (flag_minus(data));
	else if (*ptr == '+')
		return (flag_plus(data));
	else if (*ptr == ' ')
		return (flag_space(data));
	return (0);
}

int		length(const char *ptr, t_data *data)
{
	if (*ptr == 'h')
		return (length_h(ptr, data));
	else if (*ptr == 'l')
		return (length_l(ptr, data));
	else if (*ptr == 'j')
		return (length_j(data));
	else if (*ptr == 'z')
		return (length_z(data));
	return (0);
}

int		conversion(const char *ptr, va_list param, t_data *data)
{
	if (*ptr == 'S' || (*ptr == 's' && data->length[L] == 1))
		return (pick_f_bigs(param, data));
	else if (*ptr == 's')
		return (pick_f_s(param, data));
	else if (*ptr == 'p')
		return (pick_f_p(param, data, ptr));
	else if (*ptr == 'd' || *ptr == 'i' || *ptr == 'D')
		return (pick_f_d(param, data, ptr));
	else if (*ptr == 'o' || *ptr == 'O')
		return (pick_f_base(param, data, ptr));
	else if (*ptr == 'u' || *ptr == 'U')
	{
		if (*ptr == 'U')
			data->length[L] = (data->length[L] == 0) ? 1 : data->length[L];
		return (pick_f_u(param, data));
	}
	else if (*ptr == 'x' || *ptr == 'X')
		return (pick_f_base(param, data, ptr));
	else if ((*ptr == 'c' && data->length[L] == 1) || *ptr == 'C')
		return (pick_f_w(data, param));
	else if (*ptr == 'c')
		return (pick_f_c(param, data, *ptr));
	else if (*ptr == '%')
		return (pick_f_percent(data));
	return (pick_f_c(param, data, *ptr));
}
