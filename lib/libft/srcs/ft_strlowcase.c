/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:22:49 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:22:49 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlowcase(char *str)
{
	char *pstr;

	pstr = str;
	while (*pstr)
	{
		*pstr = (char)ft_tolower(*pstr);
		pstr++;
	}
	return (str);
}
