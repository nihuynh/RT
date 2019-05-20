/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:03:13 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 17:20:12 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void
	interface_mainmenu(t_ui_func *ui)
{
	if (!igBeginMainMenuBar())
		return ;
	if (igBeginMenu("Menu", 1))
	{
		igMenuItemBoolPtr("Load Scene", NULL, &ui->load_open, 1);
		igMenuItemBoolPtr("Export Scene", NULL, &ui->export_open, 1);
		igMenuItemBoolPtr("Stats", NULL, &ui->stats_open, 1);
		if (igMenuItemBoolPtr("Fullscreen", NULL, &ui->app->sdl.fullscreen, 1))
		{
			fullscreen(&ui->app->sdl, &ui->app->gui);
			ui->app->sdl.needs_render = 1;
		}
		igEndMenu();
	}
	if (igBeginMenu("Scene", 1))
	{
		igMenuItemBoolPtr("New Object", NULL, &ui->add_obj_open, 1);
		if (igMenuItemBool("New Light", NULL, 0, 1))
			new_light(ui->app);
		igMenuItemBoolPtr("Delete Selected Object", NULL,
							&ui->del_obj_open, 1);
		igEndMenu();
	}
	igEndMainMenuBar();
}
