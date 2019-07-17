/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_selector_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:51:25 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/17 18:54:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

static inline void
	obj_selector(t_gui *gui)
{
	t_list		*lst;
	t_obj		*obj;
	bool		selected;

	igText("Object Selector");
	igBeginChild("Objects Selector", (ImVec2){0, 100}, true, 0);
	lst = gui->app->scene.lst_obj;
	while (lst)
	{
		obj = lst->content;
		selected = (obj == gui->obj_set);
		if (igSelectable(obj->name, selected, 0, (ImVec2){0, 0}))
			gui->obj_set = obj;
		lst = lst->next;
	}
	igEndChild();
}

static inline void
	obj_ui_buttons(t_gui *gui)
{
	ImVec2 size;

	size = igGetWindowSize();
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Add Object", (ImVec2){size.x / 3, 0}))
		gui->add_obj_open = true;
	igSameLine(0, size.x / 6);
	if (igButton("Delete Object", (ImVec2){size.x / 3, 0}) && gui->obj_set)
		gui->del_obj_open = true;
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Add Cluster", (ImVec2){size.x / 3, 0})
		&& (gui->add_cluster_open = true))
		gui->add_obj_open = false;
	igSpacing();
}

void
	obj_ui(t_gui *gui)
{
	obj_selector(gui);
	obj_ui_buttons(gui);
	add_obj_win(gui);
	add_cluster_win(gui);
	igSeparator();
	if (gui->obj_set)
		ui_object(gui->app, gui->obj_set);
	else
		igText("Click on an object to access its data.");
	igSeparator();
	igEndTabItem();
}
