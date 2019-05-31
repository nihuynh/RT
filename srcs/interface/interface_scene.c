/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/30 15:18:25 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

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
	igCheckbox("Shadow", &app->settings.shadow);
	igSameLine(160, 0);
	igCheckbox("Facing Ratio", &app->settings.facing);
	igSameLine(320, 0);
	igCheckbox("Reflection", &app->settings.deflect);
	igCheckbox("Refraction", &app->settings.absorb);
	igSameLine(160, 0);
	igCheckbox("Anti Aliasing", &app->settings.anti_a);
	igSameLine(320, 0);
	igCheckbox("Sub-Sampling", &app->sdl->sub_s);
	igCheckbox("Show normals", &app->settings.debug_normal);
	igSameLine(160, 0);
	igCheckbox("Normal mapping", &app->settings.normal_mapping);
	color_lights(app);
	igTreePop();
	igNewLine();
}

void
	render_settings(t_data *app)
{
	igSetNextWindowPos((ImVec2){app->gui.sdl->img.width,
	app->gui.sdl->img.height + 18}, ImGuiCond_Once, (ImVec2){0, 0});
	igSetNextWindowSizeConstraints((ImVec2){500, 120}, (ImVec2){2500, 2500},
	NULL, NULL);
	if (!(igBegin("Render Settings", &app->gui.render_set_open,
	ImGuiWindowFlags_AlwaysAutoResize)))
		return ;
	if (igTreeNodeStr("Camera Settings"))
	{
		igSliderInt("Depth Max", &app->settings.depth_max, 0, 10, NULL);
		igSliderFloat("FOV", &app->settings.fov, 30, 110, "%g", 1);
		igTreePop();
	}
	if (igTreeNodeStr("Light Settings"))
		light_settings(app);
	if (igTreeNodeStr("Filters"))
	{
		if (igCheckbox("Sepia", &app->sdl->sepia))
			app->sdl->grayscale = false;
		igSameLine(160, 0);
		if (igCheckbox("GrayScale", &app->sdl->grayscale))
			app->sdl->sepia = false;
		igTreePop();
	}
	igEnd();
}

void
	scene_win(t_gui *gui)
{
	igSetNextWindowPos((ImVec2){gui->sdl->img.width, 18},
						ImGuiCond_Once, (ImVec2){0, 0});
	igSetNextWindowSizeConstraints((ImVec2){500, 120}, (ImVec2){500,
	gui->sdl->img.height}, NULL, NULL);
	igBegin("Scene", &gui->edit_open, ImGuiWindowFlags_AlwaysAutoResize);
	selector(gui);
	if (igButton("Render new frame", (ImVec2){130, 20}))
		gui->sdl->needs_render = true;
	igEnd();
}
