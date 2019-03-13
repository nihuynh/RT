/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:15:46 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:15:46 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *mem;

	if (size == 0 || !(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
