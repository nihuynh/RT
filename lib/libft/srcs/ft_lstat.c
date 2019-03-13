/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:13:24 by nihuynh           #+#    #+#             */
/*   Updated: 2018/03/30 10:13:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlist.h"

t_list	*ft_lstat(t_list *alst, unsigned int n)
{
	while (n-- && alst && alst->next)
		alst = alst->next;
	return (n == 0) ? alst : NULL;
}
