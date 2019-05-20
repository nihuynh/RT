/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:56:49 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 13:30:13 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "parse.h"

void	material_list(t_list *lst_mat, t_obj *obj)
{
	t_list		*current;
	t_material	*selected;
	t_material	*tmp;
	bool		is_selected;

	current = lst_mat;
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
}

void	texture_list(t_list *lst_tex, t_obj *obj)
{
	t_list		*current;
	t_texture	*selected;
	t_texture	*tmp;
	bool		is_selected;

	current = lst_tex;
	selected = obj->material.tex;
	if (igBeginCombo("Texture", selected->name, 0))
	{
		while (current)
		{
			tmp = current->content;
			is_selected = (ft_strcmp(selected->name, tmp->name) == 0);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
			{
				obj->material.tex = tmp;
				if (tmp->pixels == NULL)
					tmp->pixels = load_texture(tmp);
			}
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
		}
		igEndCombo();
	}
}

void	new_obj_list(int *type)
{
	const char			**item;
	static const char	*item_current;
	int					i;
	bool				is_selected;

	item = (const char*[]){"Plane", "Sphere", "Cone", "Cylinder"};
	item_current = item[*type];
	if (igBeginCombo("Object Type", item_current, 0))
	{
		i = -1;
		while (++i < 4)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				*type = i;
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
}
