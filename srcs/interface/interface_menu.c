/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:03:13 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/23 01:26:56 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"

void
	interface_mainmenu(t_gui *gui)
{
	if (!igBeginMainMenuBar())
		return ;
	if (igBeginMenu("File", 1))
	{
		igMenuItemBool("New Scene", NULL, 0, 1);
		igMenuItemBool("Open ...", NULL, 0, 1);
		igMenuItemBoolPtr("Open Scene", NULL, &gui->load_open, 1);
		igMenuItemBoolPtr("Export Scene", NULL, &gui->export_open, 1);
		igMenuItemBool("Reload Current Scene", NULL, 0, 1);
		if(igMenuItemBool("Quit", NULL, 0, 1))
			exit_safe(EXIT_SUCCESS);
		igEndMenu();
	}
	if (igBeginMenu("Edit", 1))
	{
		igMenuItemBoolPtr("New Object", NULL, &gui->add_obj_open, 1);
		if (igMenuItemBool("New Light", NULL, 0, 1))
			new_light(gui->app);
		igMenuItemBoolPtr("Delete Object", NULL, &gui->del_obj_open, 1);
		igEndMenu();
	}
	if (igBeginMenu("Window", 1))
	{
		igMenuItemBoolPtr("Stats", NULL, &gui->stats_open, 1);
		if (igMenuItemBoolPtr("Fullscreen", NULL, &gui->sdl->fullscreen, 1))
		{
			fullscreen(gui->sdl, gui);
			gui->sdl->needs_render = 1;
		}
		igEndMenu();
	}
	igEndMainMenuBar();
}
