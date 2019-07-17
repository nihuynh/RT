/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:36:15 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/17 20:45:40 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "ftlist.h"
#include "librt.h"
#include <math.h>

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

static inline int
	handle_refract(t_inter *inter, float dist_light, t_color *scalar)
{
	t_color rc;

	if (color_bool(inter->obj->material.refraction_color))
	{
		if (inter->obj->material.refract_map->f_texture)
		{
			inter_find(inter, &inter->point);
			rc = inter->obj->material.refract_map->f_texture(
				&inter->obj->material, inter->obj->material.refract_map,
				inter->obj->get_uv(inter));
		}
		else
			rc = inter->obj->material.refraction_color;
		color_mult(scalar, &rc);
		inter->dist = dist_light;
		return (0);
	}
	return (1);
}

t_color
	cast_light_primary(t_list *obj_list, t_inter *inter, float dist_light)
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
			if (handle_refract(inter, dist_light, &scalar))
				return ((t_color){0, 0, 0});
		}
		lst = lst->next;
	}
	return (scalar);
}
