/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_low.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:18:26 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/13 21:15:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"

void	ft_putnbr_base_low(int nb, unsigned int base)
{
	unsigned int	carry;
	char			*strbase;

	strbase = "0123456789abcdef";
	carry = (nb > 0) ? nb : -nb;
	if (nb < 0)
		ft_putchar('-');
	if (carry >= base)
		ft_putnbr_base_low(carry / base, base);
	ft_putchar(strbase[carry]);
}
