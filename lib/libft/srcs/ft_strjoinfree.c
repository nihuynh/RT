/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 03:21:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/22 23:58:23 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	char *res;

	if (!(res = ft_strjoin(s1, s2)))
		return (NULL);
	ft_strdel((char**)&s1);
	return (res);
}
