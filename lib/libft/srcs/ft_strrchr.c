/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:31:32 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/03 16:24:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strrchr(char const *str, int c)
{
	size_t len;

	len = ft_strlen(str);
	str += len;
	while (*str == (char)c || len--)
	{
		if (*str == (char)c)
			return ((char*)str);
		str--;
	}
	return (NULL);
}
