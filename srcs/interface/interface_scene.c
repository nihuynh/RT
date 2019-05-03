/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/03 15:52:49 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include <stdio.h>

static inline void
	color_lights(t_data *app)
{
	t_color	color_tmp;

	color_tmp = app->settings.back_color;
	if (igColorEdit3("Sky Color", &color_tmp.r, 0))
		app->settings.back_color = color_tmp;
	color_tmp = app->settings.amb_light;
	if (igColorEdit3("Ambient light color", &color_tmp.r, 0))
		app->settings.amb_light = color_tmp;
	color_tmp = app->settings.filter;
	if (igColorEdit3("Filter color", &color_tmp.r, 0))
		app->settings.filter = color_tmp;
}

static inline void
	light_settings(t_data *app)
{
	igCheckbox("Light", &app->settings.light);
	igSameLine(160, 0);
	igCheckbox("Light Intensity", &app->settings.i_light);
	igSameLine(320, 0);
	igCheckbox("Shine", &app->settings.shine);
	igSameLine(480, 0);
	igCheckbox("Shadow", &app->settings.shadow);
	igCheckbox("Facing Ratio", &app->settings.facing);
	igSameLine(160, 0);
	igCheckbox("Reflection", &app->settings.deflect);
	igSameLine(320, 0);
	igCheckbox("Refraction", &app->settings.absorb);
	igSameLine(480, 0);
	igCheckbox("Anti Aliasing", &app->settings.anti_a);
	color_lights(app);

	igTreePop();
	igNewLine();
}

static inline void
	render_settings(t_data *app)
{
	if (igTreeNodeStr("Camera Settings"))
	{
		igSliderInt("Depth Max", &app->settings.depth_max, 0, 10, NULL);
		igSliderFloat("FOV", &app->settings.fov, 30, 110, "%g", 1);
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
	igSetNextWindowPos((ImVec2){app->sdl.img.width, 0},
						ImGuiCond_Once, (ImVec2){0, 0});
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
