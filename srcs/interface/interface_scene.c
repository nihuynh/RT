/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:07:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 09:30:39 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "cimgui.h"

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
		igColorPicker3("Sky Color", color, 0);
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
	object_settings(t_data *app)
{
	if (igTreeNodeStr("Lights"))
	{
		
	}
}

static inline void
	menu_bar(t_data *app)
{
(void)app;
	if(igBeginMenu("Menu", 0))
	{
		igMenuItemBoolPtr("log", NULL, &app->gui.log_open, 1);
	}
}

void
	window_scene(t_data *app)
{
	igSetNextWindowSizeConstraints((ImVec2){800, 0}, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Scene", NULL, 0);
	if(igBeginMenuBar())
		menu_bar(app);
	if (igCollapsingHeader("Render Settings", 0))
		render_settings(app);
	if (igCollapsingHeader("Objects settings", 0))
		object_settings(app);
	igEnd();
}
