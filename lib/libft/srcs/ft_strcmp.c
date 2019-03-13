/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:21:06 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/11 02:08:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmem.h"

int		ft_strcmp(char const *s1, char const *s2)
{
	t_byte *ps1;
	t_byte *ps2;

	ps1 = (t_byte*)s1;
	ps2 = (t_byte*)s2;
	while (*ps1 && *ps2 && *ps1 == *ps2)
	{
		++ps1;
		++ps2;
	}
	return (*ps1 - *ps2);
}
