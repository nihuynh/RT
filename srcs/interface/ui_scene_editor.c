/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_scene_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 05:49:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "librt.h"
#include "config.h"

void	ui_scene_editor(t_gui *gui)
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
