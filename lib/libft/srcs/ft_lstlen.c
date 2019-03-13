/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:14:46 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:14:46 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlist.h"

size_t	ft_lstlen(t_list const *lst)
{
	size_t len;

	len = 0;
	if (lst == NULL)
		return (len);
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
