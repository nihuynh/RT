/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 17:09:01 by nihuynh          ###   ########.fr       */
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
	if (igTreeNodeStr("Filters"))
	{
		if (igCheckbox("Sepia", &app->sdl.sepia))
			app->sdl.grayscale = false;
		igSameLine(160, 0);
		if (igCheckbox("GrayScale", &app->sdl.grayscale))
			app->sdl.sepia = false;
		igTreePop();
	}
}

static inline void
	menu_bar_scene_win(t_ui_func *ui)
{
	if (igBeginMenu("Menu", 1))
	{
		igMenuItemBoolPtr("Load Scene", NULL, &ui->load_open, 1);
		igMenuItemBoolPtr("Export Scene", NULL, &ui->export_open, 1);
		igMenuItemBoolPtr("Stats", NULL, &ui->stats_open, 1);
		if (igMenuItemBoolPtr("Fullscreen", NULL, &ui->app->sdl.fullscreen, 1))
		{
			fullscreen(&ui->app->sdl, &ui->app->gui);
			ui->app->sdl.needs_render = 1;
		}
		igEndMenu();
	}
	if (igBeginMenu("Scene", 1))
	{
		igMenuItemBoolPtr("New Object", NULL, &ui->add_obj_open, 1);
		if (igMenuItemBool("New Light", NULL, 0, 1))
			new_light(ui->app);
		igMenuItemBoolPtr("Delete Selected Object", NULL,
							&ui->del_obj_open, 1);
		igEndMenu();
	}
	igEndMenuBar();
}

void
	scene_win(t_ui_func *ui)
{
	igSetNextWindowPos((ImVec2){ui->app->sdl.img.width, 0},
						ImGuiCond_Once, (ImVec2){0, 0});
	igSetNextWindowSizeConstraints((ImVec2){500, 120}, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Scene", NULL, ImGuiWindowFlags_MenuBar
		| ImGuiWindowFlags_AlwaysAutoResize);
	if (igBeginMenuBar())
		menu_bar_scene_win(ui);
	if (igCollapsingHeader("Render Settings", ImGuiTreeNodeFlags_DefaultOpen))
		render_settings(ui->app);
	if (igCollapsingHeader("Scene settings", ImGuiTreeNodeFlags_DefaultOpen))
		object_settings(ui->app);
	if (igButton("Render new frame", (ImVec2){130, 20}))
		ui->app->sdl.needs_render = true;
	igEnd();
}
