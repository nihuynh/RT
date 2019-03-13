/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 08:13:58 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_itoa_base(int value, int base)
{
	char			*res;
	char			*basestr;
	int				idx;
	unsigned int	carry;

	basestr = "0123456789ABCDEF";
	idx = (value < 0 && base == 10) ? 2 : 1;
	carry = (value > 0) ? value : -value;
	if (base < 2 || base > 16)
		return (NULL);
	while (carry /= base)
		idx++;
	carry = (value > 0) ? value : -value;
	if (!(res = ft_strnew(idx)))
		return (NULL);
	res[0] = (value < 0 && base == 10) ? '-' : basestr[0];
	while (carry)
	{
		res[--idx] = basestr[carry % base];
		carry /= base;
	}
	return (res);
}
