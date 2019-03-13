/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:06:39 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi_pf(const char *str)
{
	unsigned long	nbr;
	int				i;
	int				neg;

	i = 0;
	neg = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > 9223372036854775807ul && neg == 1)
		return (-1);
	if (nbr > 9223372036854775808ul && neg == -1)
		return (0);
	return (int)(nbr * neg);
}

int			precision(const char *ptr, t_data *data)
{
	int i;

	i = 0;
	while (*(ptr + i) >= '0' && *(ptr + i) <= '9')
		i++;
	if ((i == 1 && *ptr == '0'))
		data->precision = -1;
	else if (i > 0)
		data->precision = ft_atoi_pf(ptr);
	else
		data->precision = -1;
	return (i);
}

int			width_min(const char *ptr, t_data *data)
{
	int i;

	i = 0;
	while (*(ptr + i) >= '0' && *(ptr + i) <= '9')
		i++;
	if (i > 0)
		data->width = ft_atoi_pf(ptr);
	return (i);
}
