/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/07 17:32:43 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "librt.h"
#include "config.h"

static inline void
	camera_tab(t_data *app)
{
	t_cam	*cam;
	t_cam	tmp;

	cam = &app->cam;
	tmp = *cam;
	if (igBeginTabItem("Camera", NULL, 0))
	{
		igSliderInt("Depth Max", &app->settings.depth_max, 0, 10, NULL);
		igSliderFloat("FOV", &app->settings.fov, 30, 110, "%g", 1);
		if (igInputFloat3("Origin (X Y Z)", &tmp.pos.x, "%g", 0))
			cam->pos = tmp.pos;
		if (igSliderFloat3("Normal (X Y Z)", &tmp.dir.x, -1, 1, "%g", 1))
			cam->dir = tmp.dir;
		igEndTabItem();
	}
}

static inline void
	render_tab(t_data *app)
{
	if (igBeginTabItem("Render", NULL, 0))
	{
		igCheckbox("Light", &app->settings.light);
		igSameLine(160, 0);
		igCheckbox("Shine", &app->settings.shine);
		igCheckbox("Shadow", &app->settings.shadow);
		igSameLine(160, 0);
		igCheckbox("Facing Ratio", &app->settings.facing);
		igCheckbox("Reflection", &app->settings.deflect);
		igSameLine(160, 0);
		igCheckbox("Refraction", &app->settings.absorb);
		igNewLine();
		igCheckbox("SSAA", &app->settings.anti_a);
		igSameLine(160, 0);
		igCheckbox("Sub-Sampling", &app->sdl->sub_s);
		igCheckbox("Normal mapping", &app->settings.normal_mapping);
		igNewLine();
		igEndTabItem();
	}
}

static inline void
	scene_tab(t_data *app)
{
	t_color	color_tmp;

	if (igBeginTabItem("Scene", NULL, 0))
	{
		color_tmp = app->settings.back_color;
		if (igColorEdit3("Sky Color", &color_tmp.r, 0))
			app->settings.back_color = color_tmp;
		color_tmp = app->settings.amb_light;
		if (igColorEdit3("Ambient light color", &color_tmp.r, 0))
			app->settings.amb_light = color_tmp;
		color_tmp = app->settings.filter;
		if (igColorEdit3("Filter color", &color_tmp.r, 0))
			app->settings.filter = color_tmp;
		igEndTabItem();
	}
}

static inline void
	filter_tab(t_data *app)
{
	if (igBeginTabItem("Filters", NULL, 0))
	{
		if (igCheckbox("Sepia", &app->sdl->sepia))
			app->sdl->grayscale = false;
		igSameLine(160, 0);
		if (igCheckbox("GrayScale", &app->sdl->grayscale))
			app->sdl->sepia = false;
		igEndTabItem();
	}
}

static inline void
	debug_tab(t_data *app)
{
	if (igBeginTabItem("Debug", NULL, 0))
	{
		igCheckbox("Show normals", &app->settings.debug_normal);
		igEndTabItem();
	}
}

void
	render_settings(t_data *app)
{
	ImVec2 pos;
	ImVec2 size;

	pos.x = app->sdl->width_vp / 2.5;
	pos.y = app->sdl->height_vp * RENDER_SCALE + 18;
	size.x = app->sdl->width_vp * RENDER_SCALE - pos.x;
	size.y = app->sdl->height_vp - pos.y + 1;
	igSetNextWindowPos(pos, (ImGuiCond_Always), (ImVec2){0, 0});
	igSetNextWindowSizeConstraints(size, size, NULL, NULL);
	if (!(igBegin("Render Settings", &app->gui.render_set_open, ImGuiWindowFlags_NoResize)))
		return ;
	if (igBeginTabBar("Selector", 0))
	{
		camera_tab(app);
		render_tab(app);
		scene_tab(app);
		filter_tab(app);
		debug_tab(app);
		igEndTabBar();
	}
	if (igButton("Render new frame", (ImVec2){130, 20}))
		app->sdl->needs_render = true;
	igEnd();
}

void
	scene_win(t_gui *gui)
{
	ImVec2 pos;
	ImVec2 size;

	pos.x = gui->sdl->width_vp * RENDER_SCALE;
	pos.y = 18;
	size.x = gui->sdl->width_vp * (1 - RENDER_SCALE);
	size.y = gui->sdl->height_vp;
	igSetNextWindowPos(pos, (ImGuiCond_Always), (ImVec2){0, 0});
	igSetNextWindowSizeConstraints(size, size, NULL, NULL);
	igBegin("Scene", &gui->edit_open, ImGuiWindowFlags_AlwaysAutoResize);
	selector(gui);
	if (igButton("Render new frame", (ImVec2){130, 20}))
		gui->sdl->needs_render = true;
	igEnd();
}
