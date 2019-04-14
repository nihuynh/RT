/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/14 03:54:52 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "cimgui.h"

static inline void
	light_settings(t_data *app)
{
	float	color[3];

	igCheckbox("No Light", &app->scene_settings.no_light);
	igSameLine(160, 0);
	igCheckbox("No Light Intensity", &app->scene_settings.no_i_light);
	igSameLine(320, 0);
	igCheckbox("No Shine", &app->scene_settings.no_shine);
	igSameLine(480, 0);
	igCheckbox("No Shadow", &app->scene_settings.no_shadow);
	igSameLine(640, 0);
	igCheckbox("No Facing Ratio", &app->scene_settings.no_facing);
	igCheckbox("No Reflection", &app->scene_settings.no_deflect);
	igSameLine(160, 0);
	igCheckbox("No Refraction", &app->scene_settings.no_absorb);
	if (igTreeNodeStr("Sky Color"))
	{
		icolortogui(app->scene_settings.back_color, color);
		igColorPicker3("Sky Color", color, 0);
		guicolortoi(color, &app->scene_settings.back_color);
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
		igDragInt("Depth Max", &app->scene_settings.depth_max, 0.1, 0, 10, NULL);
		igDragFloat("FOV", &app->scene_settings.fov, 0.1, 30, 110, NULL, 1);
		igTreePop();
	}
	if (igTreeNodeStr("Light Settings"))
		light_settings(app);
	if (igButton("Apply", (ImVec2){50, 20}))
		app->sdl.needs_render = true;
}

void
	window_scene(t_data *app)
{
	igSetNextWindowSizeConstraints((ImVec2){800, 120}, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Scene", NULL, 0);
	if (igCollapsingHeader("Render Settings", 0))
		render_settings(app);
	igEnd();
}
