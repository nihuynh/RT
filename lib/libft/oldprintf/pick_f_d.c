/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_f_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:54:03 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <stdlib.h>

char			*ft_lltoa_pf(long long value)
{
	char				*res;
	size_t				idx;
	unsigned long long	carry;

	carry = (value > 0) ? value : -value;
	idx = 1;
	while (carry /= 10)
		idx++;
	carry = (value > 0) ? value : -value;
	if (!(res = ft_strnew(idx)))
		return (NULL);
	res[0] = '0';
	while (carry)
	{
		res[--idx] = carry % 10 + 48;
		carry /= 10;
	}
	return (res);
}

static void		sign_d(t_data *data, int sign)
{
	char s[2];

	s[0] = '+';
	s[1] = '-';
	if (data->flags[SPACE] == 1 && data->flags[PLUS] == 0)
	{
		s[0] = ' ';
		s[1] = '-';
	}
	if (data->width > data->precision + (int)data->len
		&& data->flags[MINUS] == 0 && data->idx >= 0 &&
		(data->flags[ZERO] == 0 || data->precision != 0))
		data->buff[data->idx] = s[sign];
	else
	{
		fill_buff_c(data, s[sign]);
		data->sign = 1;
	}
}

static void		flags_d(t_data *data, int neg, char *str, long long n)
{
	intmax_t	tmp;

	tmp = data->precision;
	data->precision = (data->precision > (int)data->len) ?
		(int)(data->precision - data->len) : 0;
	if (data->flags[MINUS] == 0 && (data->flags[ZERO] == 0 ||
				tmp != 0))
		f_width(data);
	else if (data->flags[ZERO] == 1 && data->flags[MINUS] == 0 &&
			data->precision == 0)
	{
		if ((data->flags[PLUS] == 1 || neg == 1 || data->flags[SPACE] == 1))
			sign_d(data, neg);
		f_zero(data);
	}
	if ((data->flags[PLUS] == 1 || neg == 1 || data->flags[SPACE] == 1)
		&& (data->flags[ZERO] == 0 || data->precision != 0 ||
			data->flags[MINUS] == 1))
		sign_d(data, neg);
	f_precision(data);
	if (n != 0 || tmp != -1)
		write_str(data, str);
	if (data->flags[MINUS] == 1)
		f_width(data);
}

static int		ft_int(t_data *data, long long n)
{
	char	*str;
	int		neg;

	if (n < 0)
		str = ft_lltoa_pf(-n);
	else
		str = ft_lltoa_pf(n);
	neg = (n < 0) ? 1 : 0;
	if (n != 0 || data->precision != -1)
		data->len = ft_strlen(str);
	flags_d(data, neg, str, n);
	free(str);
	return (0);
}

int				pick_f_d(va_list param, t_data *data, const char *ptr)
{
	uintmax_t n;

	if (*ptr == 'D')
		n = va_arg(param, long long int);
	else if (data->length[L] == 1)
		n = va_arg(param, long);
	else if (data->length[L] == 2)
		n = va_arg(param, long long);
	else if (data->length[Z] == 1)
		n = va_arg(param, size_t);
	else if (*ptr == 'D' || data->length[J] == 1)
		n = va_arg(param, intmax_t);
	else if (data->length[H] == 1)
		n = (short)va_arg(param, long long int);
	else if (data->length[H] == 2)
		n = (signed char)va_arg(param, int);
	else
		n = va_arg(param, int);
	ft_int(data, n);
	return (0);
}
