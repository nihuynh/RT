/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:16:21 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/17 18:52:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

static inline void
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
	light_ui(t_gui *gui)
{
	ImVec2 size;

	size = igGetWindowSize();
	light_selector(gui);
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Add Light", (ImVec2){size.x / 3, 0}))
		new_light(gui->app);
	igSameLine(0, size.x / 6);
	if (igButton("Delete Light", (ImVec2){size.x / 3, 0}) && gui->light_set)
		gui->del_light_open = true;
	igSpacing();
	igSeparator();
	if (gui->light_set)
		ui_light(gui->app, gui->light_set);
	else
		igText("Click on a light to access its data.");
	igSeparator();
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
		if (igBeginTabItem("Animations", NULL, 0))
			anim_ui(gui);
		igEndTabBar();
	}
}
