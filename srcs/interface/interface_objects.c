/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 18:00:54 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"


static inline void
	light_settings(void *res, int i)
{
	t_light			*light;
	t_pt3			tmp2;
	float			n[3];
	int				tmp;
	char			tree_name[20];

	ft_bzero(tree_name, sizeof(tree_name));
	ft_strcat(tree_name, "Light ");
	ft_strcat(tree_name, ft_itoa(i));
	light = res;
	tmp2 = light->origin;
	if (igTreeNodeStr(tree_name))
	{
		if (igInputFloat3("Position", &tmp2.x, NULL, 0))
			light->origin = tmp2;
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
		igTreePop();
	}
}

static inline void
	object(t_obj *obj)
{
	(void)obj;
	if (igTreeNodeStr("Material"))
	{
		igText(obj->material.name);
		igTreePop();
	}
}

void
	object_settings(t_data *app)
{
	t_list	*lst;
	int i;

	if (igTreeNodeStr("Lights"))
	{
		i = 0;
		lst = app->lst_light;
		while (lst)
		{
			light_settings(lst->content, i);
			lst = lst->next;
			i++;
		}
		igTreePop();
	}
	if (igTreeNodeStr("Objects"))
	{
		if (app->gui.obj_set)
			object(app->gui.obj_set);
		else
			igText("Click on an object to access its data.");
		igTreePop();
	}
}
