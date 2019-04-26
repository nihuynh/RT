/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:36:15 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/22 12:40:40 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void
	cast_primary(t_list *obj_list, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;

	lst = obj_list;
	while (lst != NULL)
	{
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		lst = lst->next;
	}
}

float
	cast_light_primary(t_list *obj_list, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;
	float	scalar;

	lst = obj_list;
	scalar = 1;
	while (lst != NULL)
	{
		inter->obj = NULL;
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		if (inter->obj != NULL)
		{
			if (inter->obj->material.absorb_idx > 0)
				scalar *= inter->obj->material.absorb_idx;
			else
				return (0);
		}
		lst = lst->next;
	}
	return (scalar);
}
