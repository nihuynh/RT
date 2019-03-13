/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:54:31 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include "ftmem.h"

static char		*address(uintptr_t nb, char *base)
{
	int			i;
	uintptr_t	prod;
	uintptr_t	tmp;
	char		*result;

	prod = 16;
	i = 0;
	tmp = nb;
	while (tmp > 0)
	{
		tmp = tmp / prod;
		i++;
	}
	if (i == 0)
		i = 1;
	if (!(result = ft_strnew((size_t)i)))
		return (NULL);
	while (--i >= 0)
	{
		result[i] = base[nb % prod];
		nb = nb / prod;
	}
	return (result);
}

static char		*add_char(char *str, char *result, int precision)
{
	int		i;
	int		j;
	int		l;

	l = (int)ft_strlen(result);
	i = 2;
	while (i + l < precision)
	{
		str[i] = '0';
		i++;
	}
	j = 0;
	while (result[j])
	{
		str[i] = result[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

static int		pick_f_p2(t_data *data, char *str, char *result)
{
	data->len = ft_strlen(result) + 2;
	print_str("0x", data, "s");
	f_zero(data);
	print_str(result, data, "s");
	ft_strdel(&result);
	ft_strdel(&str);
	return (0);
}

int				pick_f_p(va_list param, t_data *data, const char *ptr)
{
	char		*result;
	char		*str;
	uintptr_t	nb;

	nb = va_arg(param, uintptr_t);
	result = address(nb, BASE_H);
	if (data->precision > -1 && (intmax_t)ft_strlen(result) < (data->precision))
		str = ft_strnew((size_t)data->precision + 2);
	else
		str = ft_strnew(ft_strlen(result + 2));
	if (data->flags[ZERO] > 0)
		return (pick_f_p2(data, str, result));
	if (ft_memcpy(str, "0x", 2) && (nb > 0 || data->precision > 0))
		str = add_char(str, result, (int)data->precision + 2);
	data->len = ft_strlen(str);
	if (data->width > 0 && data->flags[MINUS] == 0)
		f_width_p(data, nb);
	print_str(str, data, "s");
	if (nb == 0 && data->precision == 0)
		print_str("0", data, ptr);
	if (data->flags[MINUS] == 1)
		f_width_p(data, nb);
	ft_strdel(&result);
	ft_strdel(&str);
	return (0);
}
