/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:23:48 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:23:48 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strncat(char *dst, char const *src, size_t n)
{
	char *pdst;

	pdst = dst;
	while (*pdst)
		pdst++;
	while (*src && n-- >= 1)
		*pdst++ = *src++;
	*pdst = '\0';
	return (dst);
}
