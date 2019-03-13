/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:14:02 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:14:02 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlist.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *plst;

	while (*alst)
	{
		plst = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = plst;
	}
}
