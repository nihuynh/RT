/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 03:21:07 by nihuynh           #+#    #+#             */
/*   Updated: 2018/04/23 00:28:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlist.h"

t_list	*ft_lstget(t_list *alst, int var, int (*cmp)(void *elcontent, int rv))
{
	void *content;

	while (alst)
	{
		content = alst->content;
		if (cmp(content, var))
			return (alst);
		alst = alst->next;
	}
	return (NULL);
}
