/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:16:21 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/29 19:31:42 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"
#include "libft.h"

void
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

void
	light_selector(t_gui *gui)
{
	t_list		*lst;
	t_light		*light;
	bool		selected;

	igText("Light Selector");
	igBeginChild("Light Selector", (ImVec2){0, 100}, true, 0);
	lst = gui->app->scene.lst_light;
	while (lst)
	{
		light = lst->content;
		selected = (light == gui->light_set);
		if (igSelectable(light->name, selected, 0, (ImVec2){0, 0}))
			gui->light_set = light;
		lst = lst->next;
	}
	igEndChild();
}

static inline void
	obj_ui(t_gui *gui)
{
	obj_selector(gui);
	igSpacing();
	if (igButton("New Object", (ImVec2){100, 0}))
		gui->add_obj_open = true;
	igSameLine(0, 50);
	if (igButton("Delete Object", (ImVec2){0, 0}))
		gui->del_obj_open = true;
	igSpacing();
	igSeparator();
	if (gui->obj_set)
		object(gui->app, gui->obj_set);
	else
		igText("Click on an object to access its data.");
	igEndTabItem();
}

static inline void
	light_ui(t_gui *gui)
{
	light_selector(gui);
	igSpacing();
	if (igButton("New Light", (ImVec2){100, 0}))
		new_light(gui->app);
	igSameLine(0, 50);
	if (igButton("Delete Light", (ImVec2){0, 0}))
		gui->del_light_open = true;
	igSpacing();
	igSeparator();
	if (gui->light_set)
		ui_light(gui->light_set);
	else
		igText("Click on a light to access its data.");
	igEndTabItem();
}

void
	selector(t_gui *gui)
{
	if (igBeginTabBar("Selector", 0))
	{
		if (igBeginTabItem("Objects", NULL, 0))
			obj_ui(gui);
		if (igBeginTabItem("Lights", NULL, 0))
			light_ui(gui);
		igEndTabBar();
	}
}
