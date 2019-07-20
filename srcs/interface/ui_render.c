/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:54:00 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/20 21:15:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ftstring.h"
#include "interface.h"
#include "config.h"
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
