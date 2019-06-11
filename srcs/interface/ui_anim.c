/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:26:12 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/11 15:03:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "animate.h"

static inline void
	anim_selector(t_gui *gui)
{
	t_list		*lst;
	t_anim		*anim;
	bool		selected;

	igText("Animated Object Selector");
	igBeginChild("Objects Selector", (ImVec2){0, 100}, true, 0);
	lst = gui->app->scene.lst_anim;
	while (lst)
	{
		anim = lst->content;
		selected = (anim == gui->anim_set);
		if (igSelectable(anim->obj->name, selected, 0, (ImVec2){0, 0}))
			gui->anim_set = anim;
		lst = lst->next;
	}
	igEndChild();
}

void	anim_list(t_anim *anim)
{
	const char			**item;
	static const char	*item_current;
	int					i;
	bool				is_selected;

	item = (const char*[]){"None", "Translation", "Rotation", "Orbit"};
	item_current = item[anim->type];
	if (igBeginCombo("Movement Type", item_current, 0))
	{
		i = -1;
		while (++i < 2)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				anim_set(anim, i);
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
}

static inline void
	anim_buttons(t_gui *gui, ImVec2 size)
{
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Play/Pause Animation", (ImVec2){size.x / 3, 0}))
	{
		gui->animate = 1 - gui->animate;
		gui->sdl->sub_s = 1 - gui->animate;
	}
	igSameLine(0, size.x / 6);
	if (igButton("Delete Animation", (ImVec2){size.x / 3, 0}))
		anim_delete(gui->app);
	igSpacing();
	igSameLine(size.x / 12, 0);
	if (igButton("Play One Frame", (ImVec2){size.x / 3, 0}))
		animate(gui->app);
	igSameLine(0, size.x / 6);
	if (igButton("Reset Objects Position", (ImVec2){size.x / 3, 0}))
		anim_reset(gui->app);
	igSeparator();
}

void	anim_ui(t_gui *gui)
{
	ImVec2 size;

	size = igGetWindowSize();
	anim_selector(gui);
	anim_buttons(gui, size);
	igText("Animated frames rendered : %d", gui->animated_frames);
	if (gui->anim_set)
	{
		anim_list(gui->anim_set);
		if (gui->anim_set->ui_anim)
			gui->anim_set->ui_anim(gui->anim_set);
	}
	if (igButton("render", (ImVec2){size.x / 3, 0}))
		gui->sdl->partial_render = true;
	igEndTabItem();
}
