/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_edit_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:43:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/09 11:39:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "ftmem.h"
#include "config.h"
#include "parse.h"

void
	add_obj_win(t_gui *gui)
{
	ImVec2 pos;

	if (gui->add_obj_open == false)
		return ;
	gui->add_cluster_open = false;
	pos.x = gui->sdl->width_vp * RENDER_SCALE;
	pos.y = 150;
	igSetNextWindowPos(pos, (ImGuiCond_Once), (ImVec2){0, 0});
	igSeparator();
	new_obj_list(&gui->add_obj_type);
	igSameLine(0, 10);
	if (igButton("X", (ImVec2){0, 0}))
		gui->add_obj_open = false;
	material_list(gui->app->lst_mat, &gui->mat_set);
	igSameLine(0, 10);
	if (igButton("Create", (ImVec2){0, 0}))
	{
		new_obj(gui->app, gui->add_obj_type);
		gui->add_obj_open = false;
		gui->sdl->needs_render = true;
		gui->sdl->partial_render = false;
	}
}

static inline void
	del_obj_confirmation(t_gui *gui, ImVec2 size)
{
	igText("Do you want to delete the currently selected object ?");
	igSpacing();
	igSameLine(size.x / 4, 0);
	if (igButton("Yes", (ImVec2){size.x / 8, 0}))
	{
		delete_obj(gui->app);
		gui->del_obj_open = false;
		gui->sdl->needs_render = true;
		gui->sdl->partial_render = false;
	}
	igSameLine(0, size.x / 4);
	if (igButton("No", (ImVec2){size.x / 8, 0}))
		gui->del_obj_open = false;
}

void
	del_obj_win(t_gui *gui)
{
	ImVec2	size;

	igSetNextWindowPos((ImVec2){gui->sdl->width_vp * RENDER_SCALE, 150},
		(ImGuiCond_Once), (ImVec2){0, 0});
	igBegin("Delete Object", &gui->del_obj_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	size = igGetWindowSize();
	if (gui->obj_set)
		del_obj_confirmation(gui, size);
	else
	{
		igText("You need to select an object before you can remove it");
		if (igButton("Close", (ImVec2){0, 0}))
			gui->del_obj_open = false;
	}
	igEnd();
}

static inline void
	new_cluster_list(int *type)
{
	static const char	*item_current;
	int					i;
	bool				is_selected;
	const char			*item[] = {"Tore"};

	item_current = item[*type];
	if (igBeginCombo("Cluster Type", item_current, 0))
	{
		i = -1;
		while (++i < 1)
		{
			is_selected = (item_current == item[i]);
			if (igSelectable(item[i], is_selected, 0, (ImVec2){0, 0}))
			{
				item_current = item[i];
				*type = i;
			}
			if (is_selected)
				igSetItemDefaultFocus();
		}
		igEndCombo();
	}
}

void
	add_cluster_win(t_gui *gui)
{
	ImVec2		pos;

	if (gui->add_cluster_open == false)
		return ;
	pos.x = gui->sdl->width_vp * RENDER_SCALE;
	pos.y = 150;
	igSetNextWindowPos(pos, (ImGuiCond_Once), (ImVec2){0, 0});
	igSeparator();
	new_cluster_list(&gui->cluster.type);
	igSameLine(0, 10);
	if (igButton("X", (ImVec2){0, 0}))
		gui->add_cluster_open = false;
	material_list(gui->app->lst_mat, &gui->mat_set);
	ui_cluster(&gui->cluster);
	igSameLine(0, 10);
	if (igButton("Create", (ImVec2){0, 0}))
	{
		new_cluster(gui->app, gui->cluster.type);
		ft_bzero(&gui->cluster, sizeof(t_cluster));
		gui->add_cluster_open = false;
		gui->sdl->needs_render = true;
		gui->sdl->partial_render = false;
	}
}
