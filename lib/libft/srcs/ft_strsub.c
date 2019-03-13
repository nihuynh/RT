/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:32:07 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:32:07 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (s == NULL || !(res = ft_strnew(len)))
		return (NULL);
	s += start;
	return (ft_strncpy(res, s, len));
}
