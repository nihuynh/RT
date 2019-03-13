/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:21:33 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:21:33 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"

char	*ft_strdup(char const *src)
{
	char *res;

	if (!(res = ft_strnew(ft_strlen(src))))
		return (NULL);
	return (ft_strcpy(res, src));
}
