/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:11:53 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/13 21:15:27 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"

void	ft_putnbr_base(int nb, unsigned int base)
{
	unsigned int	carry;
	char			*strbase;

	strbase = "0123456789ABCDEF";
	carry = (nb > 0) ? nb : -nb;
	if (nb < 0)
		ft_putchar('-');
	if (carry >= base)
		ft_putnbr_base(carry / base, base);
	ft_putchar(strbase[carry]);
}
