/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:23:39 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/11 02:12:42 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncasecmp(char const *s1, char const *s2, size_t n)
{
	t_byte	*ps1;
	t_byte	*ps2;
	int		res;

	ps1 = (t_byte*)s1;
	ps2 = (t_byte*)s2;
	res = 0;
	while (n-- && !res)
		res = ft_tolower(*ps1++) - ft_tolower(*ps2++);
	return (res);
}
