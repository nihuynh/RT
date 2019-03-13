/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:19:25 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:19:25 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftctype.h"

int		ft_str_is_uppercase(char *str)
{
	while (*str)
	{
		if (!(ft_isupper(*str)))
			return (0);
		str++;
	}
	return (1);
}
