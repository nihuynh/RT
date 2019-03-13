/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 03:22:17 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/22 23:57:47 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strsubfree(char const *s1, unsigned int start, size_t len)
{
	char *res;

	if (!(res = ft_strsub(s1, start, len)))
		return (NULL);
	ft_strdel((char**)&s1);
	return (res);
}
