/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:22:31 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:22:31 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t n)
{
	size_t	len;

	if (src == NULL || dst == NULL)
		return (0);
	len = ft_strlen(src);
	if (n)
	{
		n = ft_min(len, n - 1);
		ft_memcpy((void*)dst, (void*)src, n);
		dst[n] = '\0';
	}
	return (len);
}
