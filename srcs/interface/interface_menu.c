/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:03:13 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/24 02:06:03 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "config.h"
#include "libft.h"

static inline void
	file_menu(t_gui *gui)
{
	if (igMenuItemBool("New Scene", NULL, 0, 1))
		load_scene(gui->app, NEW_SCENE);
	igMenuItemBoolPtr("Open ...", NULL, &gui->load_open, 1);
	if (igBeginMenu("Open Scene", 1))
		list_scenes(gui);
	igMenuItemBoolPtr("Export Scene", NULL, &gui->export_open, 1);
	if (igMenuItemBool("Reload Current Scene", NULL, 0, 1))
		reload_scene(gui->app, gui->app->arg);
	if (igMenuItemBool("Quit", NULL, 0, 1))
		exit_safe(EXIT_SUCCESS);
	igEndMenu();
}

static inline void
	edit_menu(t_gui *gui)
{
	igMenuItemBoolPtr("New Object", NULL, &gui->add_obj_open, 1);
	if (igMenuItemBool("New Light", NULL, 0, 1))
		new_light(gui->app);
	igMenuItemBoolPtr("Delete Object", NULL, &gui->del_obj_open, 1);
	igEndMenu();
}

static inline void
	window_menu(t_gui *gui)
{
	igMenuItemBoolPtr("Tree Object", NULL, &gui->tree_open, 1);
	igMenuItemBoolPtr("Edit Scene", NULL, &gui->edit_open, 1);
	igMenuItemBoolPtr("Stats", NULL, &gui->stats_open, 1);
	if (igMenuItemBoolPtr("Fullscreen", NULL, &gui->sdl->fullscreen, 1))
	{
		fullscreen(gui->sdl, gui);
		gui->sdl->needs_render = 1;
	}
	igEndMenu();
}

void
	interface_mainmenu(t_gui *gui)
{
	if (!igBeginMainMenuBar())
		return ;
	if (igBeginMenu("File", 1))
		file_menu(gui);
	if (igBeginMenu("Edit", 1))
		edit_menu(gui);
	if (igBeginMenu("Window", 1))
		window_menu(gui);
	igEndMainMenuBar();
}
