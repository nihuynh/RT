/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_file_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:30:19 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/23 00:41:21 by nihuynh          ###   ########.fr       */
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

	ft_strcpy(buff, "scenes/");
	ft_strlcat(buff, gui->scene_name, 50 - ft_strlen(buff));
	igBegin("Export Scene", &gui->export_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, 50, ImGuiInputTextFlags_EnterReturnsTrue,
			NULL, NULL))
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
	igSetNextWindowPos((ImVec2){0, gui->sdl->img.height + 18},
		(ImGuiCond_Once), (ImVec2){0, 0});
	igBegin("Stats", &gui->stats_open, ImGuiWindowFlags_AlwaysAutoResize);
	igProgressBar(gui->sdl->progress_sub_sample, (ImVec2){150, 0}, "Render");
	igSameLine(220, 0);
	igText("Render time : %fms", (float)gui->sdl->render_time[P_TIME_LEN - 1]);
	igText("Gui FPS (%i)", (int)gui->sdl->gui_time[GUI_FPS - 1]);
	igPlotLines("Render Time (ms)", &(gui->sdl->render_time[0]),
		P_TIME_LEN, 0, NULL, 0, FLT_MAX, (ImVec2){400, 80}, 4);
	// igPlotHistogramFloatPtr("Gui FPS", &(gui->sdl->gui_time[0]),
	// 	GUI_FPS, 0, NULL, 0, 60, (ImVec2){400, 80}, 4);
	igPlotLines("Gui FPS", &(gui->sdl->gui_time[0]),
		GUI_FPS, 0, NULL, 0, 60, (ImVec2){400, 80}, 4);
	igEnd();
}
