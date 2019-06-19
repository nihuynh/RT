/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 04:37:12 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 05:29:03 by sklepper         ###   ########.fr       */
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
		}
		lst = lst->next;
	}
}

void
	anim_selector(t_gui *gui)
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
}
