/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/26 15:18:19 by sklepper         ###   ########.fr       */
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
		if (igTreeNodeStr("Color"))
		{
			color_tmp = light->color;
			if (igColorEdit3("Color", &color_tmp.r, 0))
				light->color = color_tmp;
			igTreePop();
		}
		igTreePop();
	}
}

static inline void
	material_details(t_material *mat)
{
	t_color color_tmp;

	(void)mat;
	color_tmp = mat->color_diffuse;
	if (igColorEdit3("Object Color", &color_tmp.r, 0))
		mat->color_diffuse = color_tmp;
	color_tmp = mat->color_specular;
	if (igColorEdit3("Specular Color", &color_tmp.r, 0))
		mat->color_specular = color_tmp;
	igDragFloat("Specular Index", &mat->spec_idx, 0.01, 0, 1, "%g", 1);
	igDragFloat("Specular Power", &mat->spec_power, 0.1, 0, 1000, "%g", 1);
	igDragFloat("Reflection Index", &mat->deflect_idx, 0.01, 0, 1, "%g", 1);
	igDragFloat("Refraction Index", &mat->refraction_idx, 0.01, 0, 2, "%g", 1);
	igDragFloat("Transparency", &mat->absorb_idx, 0.01, 0, 1, "%g", 1);
	igTreePop();
}

static inline void
	material(t_list *mat_lst, t_obj *obj)
{
	t_list		*current;
	t_material	*selected;
	t_material	*tmp;
	bool		is_selected;

	current = mat_lst;
	selected = &obj->material;
	tmp = current->content;
	if (igBeginCombo("Material", selected->name, 0))
	{
		while (current)
		{
			is_selected = (ft_strcmp(selected->name, tmp->name) == 0);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
				obj->material = *tmp;
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
			if (current)
				tmp = current->content;
		}
		igEndCombo();
	}
	if (igTreeNodeStr("Material Details"))
		material_details(selected);
}

static inline void
	object(t_data *app, t_obj *obj)
{
	igValueInt("Type", obj->type);
	if (igTreeNodeStr("Material"))
	{
		material(app->lst_mat, obj);
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
