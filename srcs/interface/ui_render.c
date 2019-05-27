/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:54:00 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/23 00:41:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	render_win(t_gui *gui)
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
