/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_file_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:30:19 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/27 13:37:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "rt.h"

void	err_win(t_gui *gui)
{
	igBegin("Error", &gui->err_open, ImGuiWindowFlags_AlwaysAutoResize);
	igText(gui->err_msg);
	if (igButton("Close", (ImVec2){0, 0}))
		gui->err_open = false;
	igEnd();
}

void	export_win(t_gui *gui)
{
	char buff[50];

	ft_strlcpy(buff, gui->app->arg, sizeof(buff));
	igBegin("Export Scene", &gui->export_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, sizeof(buff),
		ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
	{
		export_scene(gui->app, buff);
		gui->export_open = false;
	}
	igEnd();
}

void	load_win(t_gui *gui)
{
	char		buff[50];

	ft_strlcpy(buff, gui->app->arg, sizeof(buff));
	igBegin("Load Scene", &gui->load_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, sizeof(buff),
		ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
	{
		if (check_file(buff))
			load_scene(gui->app, buff);
		else
		{
			ft_strlcpy(gui->err_msg, "File does not exist", sizeof(gui->err_msg));
			gui->err_open = true;
		}
		gui->load_open = false;
	}
	igEnd();
}

void	stats_win(t_gui *gui)
{
	ImVec2 pos;
	ImVec2 size;
	float plot_border;

	plot_border = 10;
	if (gui->demo_open)
		igShowDemoWindow(NULL);
	pos.x = 0;
	pos.y = gui->sdl->img.height + 18;
	size.x = gui->sdl->width_vp / 2 - 17;
	size.y = gui->sdl->height_vp - pos.y + 1;
	igSetNextWindowPos(pos, (ImGuiCond_Once), (ImVec2){0, 0});
	igSetNextWindowSizeConstraints(size, (ImVec2){2500, 2500},
		NULL, NULL);
	igBegin("Stats", &gui->stats_open, ImGuiWindowFlags_NoResize);
	igText("Resolution :	[render w:%i h:%i]", gui->sdl->img.width, gui->sdl->img.height);
	igSameLine(size.x / 2, plot_border);
	igText("[app w:%i h:%i]", gui->sdl->width_vp, gui->sdl->height_vp);
	igPlotLines("", &(gui->sdl->render_time[0]), P_TIME_LEN, 0,
		NULL, 0, FLT_MAX, (ImVec2){size.x / 2, size.y / 3}, 4);
	igSameLine(size.x / 2, plot_border);
	igPlotLines("", &(gui->sdl->gui_time[0]), GUI_FPS, 0,
		NULL, 0, 60, (ImVec2){size.x / 2, size.y / 3}, 4);
	igText("Render time : %.3fms", (float)gui->sdl->render_time[P_TIME_LEN - 1]);
	igSameLine(size.x / 2, plot_border);
	igText("Gui FPS (%i)", (int)gui->sdl->gui_time[GUI_FPS - 1]);
	igProgressBar(gui->sdl->progress_sub_sample, (ImVec2){size.x / 4, 0}, "Render progress");
	igEnd();
}
