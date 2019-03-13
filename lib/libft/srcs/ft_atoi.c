/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 08:08:30 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 08:08:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftctype.h"

int		ft_atoi(char const *str)
{
	int res;
	int neg;

	res = 0;
	while (*str && (ft_isspace(*str)))
		str++;
	neg = (*str == 45) ? 1 : -1;
	if (*str && (*str == 43 || *str == 45))
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		res = res * 10 - (*str - 48);
		str++;
	}
	return (res * neg);
}
