/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_scene_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/03 03:54:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "librt.h"
#include "config.h"

void
	ui_scene_editor(t_gui *gui)
{
	ImVec2 pos;
	ImVec2 size;

	pos.x = gui->sdl->width_vp * RENDER_SCALE;
	pos.y = MENUBAR_HEIGHT;
	size.x = gui->sdl->width_vp * (1 - RENDER_SCALE);
	size.y = gui->sdl->height_vp;
	igSetNextWindowPos(pos, (ImGuiCond_Always), (ImVec2){0, 0});
	igSetNextWindowSizeConstraints(size, size, NULL, NULL);
	igBegin("Scene", &gui->edit_open, ImGuiWindowFlags_AlwaysAutoResize);
	selector(gui);
	if (igButton("Render new frame", (ImVec2){size.x / 3, 20}))
		gui->sdl->needs_render = true;
	igEnd();
}

void
	del_light_win(t_gui *gui)
{
	igBegin("Delete Object", &gui->del_light_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (gui->light_set)
	{
		igText("Do you want to delete the currently selected light ?");
		if (igButton("Yes", (ImVec2){0, 20}))
		{
			delete_light(gui->app);
			gui->del_light_open = false;
			gui->sdl->needs_render = true;
			gui->sdl->partial_render = false;
		}
		igSameLine(0, 0);
		if (igButton("No", (ImVec2){0, 0}))
			gui->del_light_open = false;
	}
	else
	{
		igText("You need to select a light before you can remove it");
		if (igButton("Close", (ImVec2){0, 0}))
			gui->del_light_open = false;
	}
	igEnd();
}
