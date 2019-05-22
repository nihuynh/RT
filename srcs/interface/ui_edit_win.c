/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_edit_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:43:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/23 00:41:09 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "ftmem.h"

void	add_obj_win(t_gui *gui)
{
	if (gui->add_obj_open == false)
		return ;
	igBegin("New Object", &gui->add_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	new_obj_list(&gui->add_obj_type);
	igSameLine(0, 0);
	if (igButton("Create", (ImVec2){0, 0}))
	{
		new_obj(gui->app, gui->add_obj_type);
		gui->add_obj_open = false;
		gui->sdl->needs_render = true;
		gui->sdl->partial_render = false;
	}
	igEnd();
}

void	del_obj_win(t_gui *gui)
{
	if (gui->del_obj_open == false)
		return ;
	igBegin("Delete Object", &gui->del_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (gui->obj_set)
	{
		igText("Do you want to delete the currently selected object ?");
		if (igButton("Yes", (ImVec2){0, 0}))
		{
			delete_obj(gui->app);
			gui->del_obj_open = false;
			gui->sdl->needs_render = true;
			gui->sdl->partial_render = false;
		}
		igSameLine(0, 0);
		if (igButton("No", (ImVec2){0, 0}))
			gui->del_obj_open = false;
	}
	else
	{
		igText("You need to select an object before you can remove it");
		if (igButton("Close", (ImVec2){0, 0}))
			gui->del_obj_open = false;
	}
	igEnd();
}
