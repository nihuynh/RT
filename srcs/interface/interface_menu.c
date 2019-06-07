/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:03:13 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/07 14:19:02 by nihuynh          ###   ########.fr       */
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
	igMenuItemBoolPtr("Save Scene", NULL, &gui->export_open, 1);
	if (igMenuItemBool("Reload Current Scene", NULL, 0, 1))
		reload_scene(gui->app, gui->app->arg);
	if (igMenuItemBool("Quit", "Esc or Cmd + Q", 0, 1))
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
	igMenuItemBoolPtr("Delete Light", NULL, &gui->del_light_open, 1);
	igEndMenu();
}

static inline void
	window_menu(t_gui *gui)
{
	igMenuItemBoolPtr("Scene Editor", NULL, &gui->edit_open, 1);
	igMenuItemBoolPtr("Camera Editor", NULL, &gui->cam_open, 1);
	igMenuItemBoolPtr("Render Settings", NULL, &gui->render_set_open, 1);
	igMenuItemBoolPtr("Stats", NULL, &gui->stats_open, 1);
	if (igMenuItemBoolPtr("Fullscreen", NULL, &gui->sdl->fullscreen, 1))
	{
		fullscreen(gui->sdl, gui);
		gui->stats_open = 0;
		gui->sdl->needs_render = 1;
	}
	igMenuItemBoolPtr("Demo", NULL, &gui->demo_open, 1);
	if (igBeginMenu("Resolutions", 1))
	{
		if (igMenuItemBool("840x500", NULL, (gui->sdl->height_vp == 500), 1))
			resize_app(800, 500, gui->app);
		if (igMenuItemBool("1680x1000", NULL, (gui->sdl->height_vp == 1000), 1))
			resize_app(1680, 1000, gui->app);
		if (igMenuItemBool("2560x1400", NULL, (gui->sdl->height_vp == 1400), 1))
			resize_app(2560, 1400, gui->app);
		if (igMenuItemBool("3200x1800", NULL, (gui->sdl->height_vp == 1800), 1))
			resize_app(3200, 1800, gui->app);
		igEndMenu();
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
