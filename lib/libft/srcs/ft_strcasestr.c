/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:20:21 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:20:21 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcasestr(char const *s, char const *ne)
{
	size_t len;

	if (!(len = ft_strlen(ne)))
		return ((char*)s);
	while (*s)
	{
		if (ft_tolower(*s) == ft_tolower(*ne) && !(ft_strncasecmp(s, ne, len)))
			return ((char*)s);
		s++;
	}
	return (NULL);
}
