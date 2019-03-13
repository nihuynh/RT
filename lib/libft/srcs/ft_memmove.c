/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:16:58 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/03 17:46:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"

void	*ft_memmove(void *dst, void const *src, size_t n)
{
	if (n == 0 || dst == src)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, n);
	else
		ft_memrcpy(dst, src, n);
	return (dst);
}
