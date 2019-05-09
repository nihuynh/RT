/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_windows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:28:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/09 17:34:55 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"
#include "libft.h"

void	error_window(t_data *app)
{
	igBegin("Error", &app->gui.error_open, ImGuiWindowFlags_AlwaysAutoResize);
	igText("File not found");
	if (igButton("Close", (ImVec2){0, 0}))
		app->gui.error_open = false;
	igEnd();
}

void	export_window(t_data *app)
{
	char buff[30];

	ft_strcpy(buff, app->gui.scene_name);
	igBegin("Export Scene", &app->gui.export_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, 30, ImGuiInputTextFlags_EnterReturnsTrue,
			NULL, NULL))
	{
		export_scene(app, buff);
		app->gui.export_open = false;
	}
	igEnd();
}

void	new_obj_window(t_data *app)
{
	igBegin("New Object", &app->gui.new_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	new_obj_list(&app->gui.new_obj_type);
	igSameLine(0, 0);
	if (igButton("Create", (ImVec2){0, 0}))
	{
		new_obj(app, app->gui.new_obj_type);
		app->gui.new_obj_open = false;
		app->sdl.needs_render = true;
	}
	igEnd();
}

void	delete_obj_window(t_data *app)
{
	igBegin("Delete Object", &app->gui.delete_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (app->gui.obj_set)
	{
		igText("Do you want to delete the currently selected object ?");
		if (igButton("Yes", (ImVec2){0, 0}))
		{
			delete_obj(app);
			app->gui.delete_obj_open = false;
			app->sdl.needs_render = true;
		}
		igSameLine(0, 0);
		if (igButton("No", (ImVec2){0, 0}))
			app->gui.delete_obj_open = false;
	}
	else
	{
		igText("You need to select an object before you can remove it");
		if (igButton("Close", (ImVec2){0, 0}))
			app->gui.delete_obj_open = false;
	}
	igEnd();
}

void	load_window(t_data *app)
{
	char buff[50];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, app->arg);
	igBegin("Load Scene", &app->gui.load_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, 50, ImGuiInputTextFlags_EnterReturnsTrue,
			NULL, NULL))
	{
		if (check_file(buff))
			reload(app, buff);
		else
			app->gui.error_open = true;
		app->gui.load_open = false;
	}
	igEnd();
}
