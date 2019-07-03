/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:54:00 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/03 03:14:06 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ftstring.h"
#include "interface.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "config.h"
#include "SDL_opengl.h"
#include "librt.h"

void
	render_win(t_gui *gui)
{
	ImVec2	pos;

	igSetNextWindowPos((ImVec2){0, 18}, gui->flags_render, (ImVec2){0, 0});
	igSetNextWindowSize((ImVec2){gui->sdl->img.width,
								gui->sdl->img.height}, 0);
	igPushStyleVarVec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0);
	igBegin("render", NULL, RENDER_FLAGS);
	igImage((void*)(intptr_t)gui->texture_id,
		(ImVec2){gui->sdl->img.width, gui->sdl->img.height},
		(ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){1, 1, 1, 1},
		(ImVec4){0, 0, 0, 0});
	pos = igGetWindowPos();
	gui->pos_render.x = pos.x;
	gui->pos_render.y = pos.y;
	gui->render_focused = !igIsWindowFocused(0);
	igEnd();
	igPopStyleVar(2);
}

void
	keymap_win(t_gui *gui)
{
	char	*abs_path;
	ImVec2	img_size;

	if (gui->keymap.name == NULL)
	{
		abs_path = ft_strjoin(gui->app->option.path, KEYMAP_PATH);
		gui->keymap.name = ft_strdup("keymap");
		gui->keymap.dir = abs_path;
		load_nbind_texture(&gui->keymap, &gui->keymap_id);
	}
	igBegin("Keymap", &gui->keymap_open, ImGuiWindowFlags_AlwaysAutoResize);
	img_size.x = gui->keymap.width;
	img_size.y = gui->keymap.height;
	igText("%.0fx%.0f", img_size.x, img_size.y);
	igImage((void*)(intptr_t)gui->keymap_id,
		img_size, (ImVec2){0.0f, 0.0f}, (ImVec2){1.0f, 1.0f},
		(ImVec4){1.0f, 1.0f, 1.0f, 1.0f}, (ImVec4){1.0f, 1.0f, 1.0f, 0.5f});
	igEnd();
}

void
	about_win(t_gui *gui)
{
	igBegin("About", &gui->about_open, ImGuiWindowFlags_AlwaysAutoResize);
	igText("Created by : Nicolas Huynh, Samuel Klepper, Thibault D'archivio");
	igText("Made in 2019 @42 Paris");
	igEnd();
}

void
	ui_tore(void *app_v, void *res)
{
	t_tore	*tore;
	t_tore	tmp;

	(void)app_v;
	tore = res;
	tmp = *tore;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		tore->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		tore->n = tmp.n;
	if (igSliderFloat3("X (X Y Z)", &tmp.x.x, -1, 1, "%g", 1))
		tore->x = tmp.x;
	if (igSliderFloat3("Z (X Y Z)", &tmp.z.x, -1, 1, "%g", 1))
		tore->z = tmp.z;
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&tore->n);
		vec3_normalize(&tore->x);
		vec3_normalize(&tore->z);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		tore->size = tmp.size;
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		tore->radius = tmp.radius;
}

void
	ui_cube(void *app_v, void *res)
{
	t_cube	*cube;
	t_cube	tmp;

	(void)app_v;
	cube = res;
	tmp = *cube;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		cube->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cube->n = tmp.n;
	if (igSliderFloat3("X (X Y Z)", &tmp.x.x, -1, 1, "%g", 1))
		cube->x = tmp.x;
	if (igSliderFloat3("Z (X Y Z)", &tmp.z.x, -1, 1, "%g", 1))
		cube->z = tmp.z;
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&cube->n);
		vec3_normalize(&cube->x);
		vec3_normalize(&cube->z);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		cube->size = tmp.size;
}
