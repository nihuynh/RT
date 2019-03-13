/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 03:22:06 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/22 03:23:21 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

static int	ft_scan(char c, char const *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

char		*ft_strpbrk(char const *s1, char const *s2)
{
	char *ps1;

	ps1 = (char*)s1;
	while (*ps1)
	{
		if (ft_scan(*ps1, s2))
			return (ps1);
		ps1++;
	}
	return (NULL);
}
