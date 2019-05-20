/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hook_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:54:00 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 17:20:03 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	render_window(t_ui_func *ui)
{
	ImVec2	pos;

	igSetNextWindowPos((ImVec2){0, 18}, ui->flags_render, (ImVec2){0, 0});
	igSetNextWindowSize((ImVec2){ui->app->sdl.img.width,
								ui->app->sdl.img.height}, 0);
	igPushStyleVarVec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0);
	igBegin("render", NULL, RENDER_FLAGS);
	igImage((void*)(intptr_t)ui->app->gui.texture_id,
		(ImVec2){ui->app->sdl.img.width, ui->app->sdl.img.height},
		(ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){1, 1, 1, 1},
		(ImVec4){0, 0, 0, 0});
	pos = igGetWindowPos();
	ui->app->gui.pos_render.x = pos.x;
	ui->app->gui.pos_render.y = pos.y;
	ui->app->gui.render_focused = !igIsWindowFocused(0);
	igEnd();
	igPopStyleVar(2);
}

void	ui_hook_render(t_ui_func *ui)
{
	ui->render_win = &render_window;
	ui->scene_win = &scene_window;
	// ui_func->menu_bar = &menu_bar;
	// ui_func->FUNCTION_ = &FUNCTION__window;
}
