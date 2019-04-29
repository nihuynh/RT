/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/29 19:04:14 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

static inline void
	light_settings(void *res, int i)
{
	t_light			*light;
	t_pt3			origin_tmp;
	t_color			color_tmp;
	char			tree_name[20];

	ft_bzero(tree_name, sizeof(tree_name));
	ft_strcat(tree_name, "Light ");
	ft_strcat(tree_name, ft_itoa(i));
	light = res;
	if (igTreeNodeStr(tree_name))
	{
		origin_tmp = light->origin;
		if (igInputFloat3("Position (X Y Z)", &origin_tmp.x, "%g", 0))
			light->origin = origin_tmp;
		igInputFloat("Intensity", &light->intensity, 0, 0, "%g", 0);
		color_tmp = light->color;
		if (igColorEdit3("Color", &color_tmp.r, 0))
			light->color = color_tmp;
		igTreePop();
	}
}

static inline void
	material_details(t_material *mat)
{
	t_color color_tmp;

	color_tmp = mat->color_diffuse;
	if (igColorEdit3("Object Color", &color_tmp.r, 0))
		mat->color_diffuse = color_tmp;
	color_tmp = mat->color_specular;
	if (igColorEdit3("Specular Color", &color_tmp.r, 0))
		mat->color_specular = color_tmp;
	igDragFloat("Specular Index", &mat->spec_idx, 0.01, 0, 1, "%g", 1);
	igDragFloat("Specular Power", &mat->spec_power, 0.1, 0, 1000, "%g", 1);
	color_tmp = mat->reflection_color;
	if (igColorEdit3("Reflection Color", &color_tmp.r, 0))
		mat->reflection_color = color_tmp;
	igDragFloat("Refraction Index", &mat->refraction_idx, 0.01, 0, 2, "%g", 1);
	color_tmp = mat->refraction_color;
	if (igColorEdit3("Refraction Color", &color_tmp.r, 0))
		mat->refraction_color = color_tmp;
	igTreePop();
}

static inline void
	material(t_data *app, t_obj *obj)
{
	material_list(app->lst_mat, obj);
	texture_list(app->lst_tex, obj);
	if (igTreeNodeStr("Material Details"))
		material_details(&obj->material);
}

static inline void
	object(t_data *app, t_obj *obj)
{
	igValueInt("Type", obj->type);
	if (igTreeNodeStr("Material"))
	{
		material(app, obj);
		igTreePop();
	}
	if (igTreeNodeStr("Object"))
	{
		obj->f_gui(obj->shape);
		igTreePop();
	}
}

void
	object_settings(t_data *app)
{
	t_list	*lst;
	int		i;

	if (igTreeNodeStr("Lights"))
	{
		i = 0;
		lst = app->scene.lst_light;
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
			object(app, app->gui.obj_set);
		else
			igText("Click on an object to access its data.");
		igTreePop();
	}
}
