/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 04:46:44 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftconvert.h"
#include "ftstring.h"
#include <stdlib.h>

static inline char	*ft_itoa_signed(int value, int signe, int dot)
{
	char			*res;
	int				ndx;
	unsigned int	carry;

	carry = (value > 0) ? value : -value;
	ndx = 1 + dot + signe;
	while (carry /= 10)
		ndx++;
	carry = (value > 0) ? value : -value;
	if (!(res = ft_strnew(ndx)))
		return (NULL);
	if (signe)
		res[0] = '-';
	if (dot)
		res[--ndx] = '.';
	if (!carry)
		res[--ndx] = '0';
	while (carry)
	{
		res[--ndx] = carry % 10 + 48;
		carry /= 10;
	}
	return (res);
}

char				*ft_dtoa(double value, int precision)
{
	char			*unitstr;
	char			*decistr;
	char			*dest;
	unsigned int	carry;

	if (!(unitstr = ft_itoa_signed((int)value, value < 0, precision > 0)))
		return (NULL);
	value = (value > 0) ? value : -value;
	value -= (value > 0) ? (int)value : (int)-value;
	carry = 1;
	if (precision <= 0)
		return (unitstr);
	while (precision--)
		carry *= 10;
	carry *= value;
	if (!(decistr = ft_itoa(carry)))
		return (NULL);
	if (!(dest = ft_strjoin(unitstr, decistr)))
		return (NULL);
	free(unitstr);
	free(decistr);
	return (dest);
}
