/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:15:24 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:15:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlist.h"

void	ft_lstrev(t_list **alst)
{
	t_list	*palst;
	t_list	*tmp;

	tmp = NULL;
	if (!alst || !*alst)
		return ;
	while (*alst)
	{
		palst = (*alst)->next;
		(*alst)->next = tmp;
		tmp = *alst;
		*alst = palst;
	}
	*alst = tmp;
}
