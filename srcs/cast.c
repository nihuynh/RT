/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:36:15 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/15 17:42:39 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void
	cast_primary(t_data *data, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->lst_obj;
	while (lst != NULL)
	{
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		lst = lst->next;
	}
}

void
	cast_light_primary(t_data *data, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->lst_obj;
	while (lst != NULL)
	{
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		if (inter->obj != NULL)
			return ;
		lst = lst->next;
	}
}
