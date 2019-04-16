/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 16:00:02 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include <stdio.h>

static inline void
	light_settings(t_data *app)
{
	float	color[3];

	igCheckbox("No Light", &app->scene_set.no_light);
	igSameLine(160, 0);
	igCheckbox("No Light Intensity", &app->scene_set.no_i_light);
	igSameLine(320, 0);
	igCheckbox("No Shine", &app->scene_set.no_shine);
	igSameLine(480, 0);
	igCheckbox("No Shadow", &app->scene_set.no_shadow);
	igSameLine(640, 0);
	igCheckbox("No Facing Ratio", &app->scene_set.no_facing);
	igCheckbox("No Reflection", &app->scene_set.no_deflect);
	igSameLine(160, 0);
	igCheckbox("No Refraction", &app->scene_set.no_absorb);
	if (igTreeNodeStr("Sky Color"))
	{
		icolortogui(app->scene_set.back_color, color);
		if (igColorEdit3("Sky Color", color, 0))
			guicolortoi(color, &app->scene_set.back_color);
		igTreePop();
	}
	igTreePop();
	igNewLine();
}

static inline void
	render_settings(t_data *app)
{
	if (igTreeNodeStr("Camera Settings"))
	{
		igDragInt("Depth Max", &app->scene_set.depth_max, 0.1, 0, 10, NULL);
		igDragFloat("FOV", &app->scene_set.fov, 0.1, 30, 110, NULL, 1);
		igTreePop();
	}
	if (igTreeNodeStr("Light Settings"))
		light_settings(app);
	if (igButton("Apply", (ImVec2){50, 20}))
		app->sdl.needs_render = true;
}

static inline void
	menu_bar(t_data *app)
{
	if(igBeginMenu("Menu", 1))
	{
		igMenuItemBoolPtr("log", NULL, &app->gui.log_open, 1);
		igEndMenu();
	}
	igEndMenuBar();
}

void
	window_scene(t_data *app)
{
	igSetNextWindowSizeConstraints((ImVec2){800, 120}, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Scene", NULL, ImGuiWindowFlags_MenuBar);
	if(igBeginMenuBar())
		menu_bar(app);
	if (igCollapsingHeader("Render Settings", 0))
		render_settings(app);
	if (igCollapsingHeader("Objects settings", 0))
		object_settings(app);
	igEnd();
}
