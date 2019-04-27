/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:36:15 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/26 16:02:48 by sklepper         ###   ########.fr       */
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

t_color
	cast_light_primary(t_list *obj_list, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;
	t_color	scalar;

	lst = obj_list;
	scalar = (t_color){1, 1, 1};
	while (lst != NULL)
	{
		inter->obj = NULL;
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		if (inter->obj != NULL)
		{
			if (bool_color(inter->obj->material.refraction_color))
				color_mult(&scalar, &inter->obj->material.refraction_color);
			else
				return ((t_color){0, 0, 0});
		}
		lst = lst->next;
	}
	return (scalar);
}
