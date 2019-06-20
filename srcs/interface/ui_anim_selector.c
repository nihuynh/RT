/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 04:37:12 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/20 16:57:46 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "animate.h"
#include "libft.h"

static inline void
	anim_selector_camera(t_gui *gui)
{
	bool	selected;

	selected = (gui->app->cam.anim == gui->anim_set);
	if (igSelectable("Camera", selected, 0, (ImVec2){0, 0}))
	{
		gui->anim_set = gui->app->cam.anim;
		gui->lst_anim_set = NULL;
	}
	igSeparator();
}

static inline void
	anim_selector_obj(t_gui *gui)
{
	t_list		*lst;
	t_anim		*anim;
	bool		selected;

	lst = gui->app->scene.lst_anim;
	while (lst)
	{
		anim = lst->content;
		selected = (anim == gui->anim_set);
		if (igSelectable(anim->obj->name, selected, 0, (ImVec2){0, 0}))
		{
			gui->anim_set = anim;
			gui->lst_anim_set = lst;
			gui->alst = &gui->app->scene.lst_anim;
		}
		lst = lst->next;
	}
	igSeparator();
}

static inline void
	anim_selector_light(t_gui *gui)
{
	t_list		*lst;
	t_anim		*anim;
	bool		selected;

	lst = gui->app->scene.lst_anim_light;
	while (lst)
	{
		anim = lst->content;
		selected = (anim == gui->anim_set);
		if (igSelectable(anim->light->name, selected, 0, (ImVec2){0, 0}))
		{
			gui->anim_set = anim;
			gui->lst_anim_set = lst;
			gui->alst = &gui->app->scene.lst_anim_light;
		}
		lst = lst->next;
	}
}

void
	anim_selector(t_gui *gui, ImVec2 size)
{
	igText("Animated Object Selector");
	igBeginChild("Objects Selector", (ImVec2){0, 100}, true, 0);
	if (gui->app->cam.anim)
		anim_selector_camera(gui);
	if (gui->app->scene.lst_anim)
		anim_selector_obj(gui);
	if (gui->app->scene.lst_anim_light)
		anim_selector_light(gui);
	igEndChild();
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Move Down", (ImVec2){size.x / 3, 0}) && gui->lst_anim_set)
		ft_lstmovedown(gui->alst, gui->lst_anim_set);
	igSameLine(0, size.x / 6);
	if (igButton("Move Up", (ImVec2){size.x / 3, 0}) && gui->lst_anim_set)
		ft_lstmoveup(gui->alst, gui->lst_anim_set);
	igSeparator();
}
