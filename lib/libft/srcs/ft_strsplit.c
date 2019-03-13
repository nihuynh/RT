/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:31:46 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"
#include <stdlib.h>

char	**ft_strsplit(char const *str, char c)
{
	char	**res;
	size_t	idx;
	size_t	wordlen;

	if (str == NULL)
		return (NULL);
	idx = 0;
	if (!(res = (char**)malloc((ft_wordcount(str, c) + 1) * sizeof(char*))))
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			wordlen = ft_strclen(str, c);
			if (!(res[idx] = ft_strnew(wordlen)))
				return (NULL);
			ft_strncpy(res[idx], str, wordlen);
			str += wordlen;
			idx++;
		}
	}
	res[idx] = NULL;
	return (res);
}
