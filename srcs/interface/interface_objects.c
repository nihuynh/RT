/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/18 14:15:37 by sklepper         ###   ########.fr       */
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
		if (igInputFloat3("Position", &origin_tmp.x, NULL, 0))
			light->origin = origin_tmp;
		igInputFloat("Intensity", &light->intensity, 0, 0, NULL, 0);
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
	material(t_list *mat_lst)
{
	t_list		*current;
	t_material	*selected;
	t_material	*tmp;
	bool		is_selected;

	current = mat_lst;
	selected = mat_lst->content;
	tmp = mat_lst->content;
	if(igBeginCombo("Material", selected->name, 0))
	{
		while (tmp)
		{
			is_selected = (selected == tmp);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){40, 20}))
				selected = tmp;
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
			tmp = current->content;
		}
		igEndCombo();
	}
}

static inline void
	object(t_data *app, t_obj *obj)
{
	(void)obj;
	if (igTreeNodeStr("Material"))
		material(app->lst_mat);
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
			object(app, app->gui.obj_set);
		else
			igText("Click on an object to access its data.");
		igTreePop();
	}
}
