/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:16:15 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:16:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"

void	*ft_memchr(void const *str, int c, size_t n)
{
	t_byte *pstr;

	pstr = (t_byte*)str;
	while (n--)
	{
		if (*pstr == (t_byte)c)
			return ((void *)pstr);
		pstr++;
	}
	return (NULL);
}
