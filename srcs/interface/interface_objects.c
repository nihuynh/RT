/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 15:41:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static inline void
	light_settings(void *res)
{
	t_light		*light;
	float			n[3];
	int				tmp;

	light = res;
	cpy_pos(light->origin, n);
	if (igInputFloat3("Position", n, NULL, 0))
		cpy_pos_rev(n, &light->origin);
	igInputFloat("Intensity", &light->intensity, 0, 0, NULL, 0);
	if (igTreeNodeStr("Color"))
	{
		tmp = colortoi(&light->color);
		icolortogui(tmp, n);
		if (igColorEdit3("Color", n, 0))
		{
			guicolortoi(n, &tmp);
			itocolor(&light->color, tmp);
		}
		igTreePop();
	}
}

void
	object_settings(t_list *light_lst, t_list *obj_lst)
{
	if (igTreeNodeStr("Lights"))
	{
		light_settings(light_lst->content);
		igTreePop();
	}
	(void)obj_lst;
}
