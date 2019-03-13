/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 08:09:40 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/26 15:30:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"

void	ft_bzero(void *str, size_t n)
{
	t_byte	*pstr;
	t_byte	val;

	pstr = (t_byte*)str;
	val = 0;
	while (n--)
		*pstr++ = val;
}
