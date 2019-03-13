/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:16:38 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_tabdel(char **greed)
{
	int i;

	i = -1;
	if (greed == NULL)
		return ;
	while (greed[++i])
		free(greed[i]);
	free(greed);
}
