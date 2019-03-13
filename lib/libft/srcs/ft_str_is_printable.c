/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:19:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:19:45 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftctype.h"

int		ft_str_is_printable(char *str)
{
	while (*str)
	{
		if (!(ft_isprint(*str)))
			return (0);
		str++;
	}
	return (1);
}
