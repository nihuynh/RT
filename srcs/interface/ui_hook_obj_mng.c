/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hook_obj_mng.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:43:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 20:46:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "ftmem.h"

void	add_obj_window(t_ui_func *ui)
{
	if (ui->add_obj_open == false)
		return ;
	igBegin("New Object", &ui->add_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	new_obj_list(&ui->add_obj_type);
	igSameLine(0, 0);
	if (igButton("Create", (ImVec2){0, 0}))
	{
		new_obj(ui->app, ui->add_obj_type);
		ui->add_obj_open = false;
		ui->app->sdl.needs_render = true;
	}
	igEnd();
}

void	del_obj_window(t_ui_func *ui)
{
	if (ui->del_obj_open == false)
		return ;
	igBegin("Delete Object", &ui->del_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (ui->app->gui.obj_set)
	{
		igText("Do you want to delete the currently selected object ?");
		if (igButton("Yes", (ImVec2){0, 0}))
		{
			delete_obj(ui->app);
			ui->del_obj_open = false;
			ui->app->sdl.needs_render = true;
		}
		igSameLine(0, 0);
		if (igButton("No", (ImVec2){0, 0}))
			ui->del_obj_open = false;
	}
	else
	{
		igText("You need to select an object before you can remove it");
		if (igButton("Close", (ImVec2){0, 0}))
			ui->del_obj_open = false;
	}
	igEnd();
}

void	ui_hook_obj_mng(t_ui_func *ui_func)
{
	ui_func->add_obj_win = &add_obj_window;
	ui_func->del_obj_win = &del_obj_window;
	// ui_func->FUNCTION_ = &FUNCTION__window;
	// ui_func->FUNCTION_ = &FUNCTION__window;
}
