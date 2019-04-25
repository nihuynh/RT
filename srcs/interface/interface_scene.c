/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/25 15:16:35 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include <stdio.h>

static inline void
	light_settings(t_data *app)
{
	t_color	color_tmp;

	igCheckbox("Light", &app->scene_set.light);
	igSameLine(160, 0);
	igCheckbox("Light Intensity", &app->scene_set.i_light);
	igSameLine(320, 0);
	igCheckbox("Shine", &app->scene_set.shine);
	igSameLine(480, 0);
	igCheckbox("Shadow", &app->scene_set.shadow);
	igCheckbox("Facing Ratio", &app->scene_set.facing);
	igSameLine(160, 0);
	igCheckbox("Reflection", &app->scene_set.deflect);
	igSameLine(320, 0);
	igCheckbox("Refraction", &app->scene_set.absorb);
	color_tmp = app->scene_set.back_color;
	if (igColorEdit3("Sky Color", &color_tmp.r, 0))
		app->scene_set.back_color = color_tmp;
	color_tmp = app->scene_set.amb_light;
	if (igColorEdit3("Ambient light color", &color_tmp.r, 0))
		app->scene_set.amb_light = color_tmp;
	igTreePop();
	igNewLine();
}

static inline void
	render_settings(t_data *app)
{
	if (igTreeNodeStr("Camera Settings"))
	{
		igSliderInt("Depth Max", &app->scene_set.depth_max, 0, 10, NULL);
		igSliderFloat("FOV", &app->scene_set.fov, 30, 110, "%g", 1);
		igTreePop();
	}
	if (igTreeNodeStr("Light Settings"))
		light_settings(app);
}

static inline void
	menu_bar(t_data *app)
{
	if (igBeginMenu("Menu", 1))
	{
		igMenuItemBoolPtr("log", NULL, &app->gui.log_open, 1);
		if (igMenuItemBoolPtr("Fullscreen", NULL, &app->sdl.fullscreen, 1))
			app->sdl.needs_render = 1;
		igEndMenu();
	}
	igEndMenuBar();
}

void
	window_scene(t_data *app)
{
	igSetNextWindowSizeConstraints((ImVec2){800, 120}, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Scene", NULL, ImGuiWindowFlags_MenuBar
		| ImGuiWindowFlags_AlwaysAutoResize);
	if (igBeginMenuBar())
		menu_bar(app);
	if (igCollapsingHeader("Render Settings", ImGuiTreeNodeFlags_DefaultOpen))
		render_settings(app);
	if (igCollapsingHeader("Scene settings", ImGuiTreeNodeFlags_DefaultOpen))
		object_settings(app);
	if (igButton("Render new frame", (ImVec2){130, 20}))
		app->sdl.needs_render = true;
	igEnd();
}
