/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:19:16 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:19:16 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftctype.h"

int		ft_str_is_lowercase(char *str)
{
	while (*str)
	{
		if (!(ft_islower(*str)))
			return (0);
		str++;
	}
	return (1);
}
