/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:23:16 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strmapi(char const *str, char (*f) (unsigned int, char))
{
	size_t			len;
	char			*res;
	unsigned int	idx;

	if (!f || !str)
		return (NULL);
	len = ft_strlen(str);
	if (!(res = ft_strnew(len)))
		return (NULL);
	idx = 0;
	while (*str)
		*res++ = f(idx++, *str++);
	res -= len;
	return (res);
}
