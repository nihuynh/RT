/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_file_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:30:19 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/26 00:54:21 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "config.h"

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
			ft_strlcpy(gui->err_msg, "File don't exist", sizeof(gui->err_msg));
			gui->err_open = true;
		}
		gui->load_open = false;
	}
	igEnd();
}

void	stats_win_content(t_sdl *sdl, ImVec2 size, t_data *app)
{
	float plot_border;

	plot_border = 10;
	igText("Resolution : [img w:%i h:%i]", sdl->img.width, sdl->img.height);
	igSameLine(size.x / 2 + 10, plot_border);
	igText("[app w:%i h:%i]", sdl->width_vp, sdl->height_vp);
	igPlotLines("", &(sdl->render_time[0]), P_TIME_LEN, 0,
		NULL, 0, FLT_MAX, (ImVec2){size.x / 2, size.y / 3}, 4);
	igSameLine(size.x / 2, plot_border);
	igPlotLines("", &(sdl->gui_time[0]), GUI_FPS, 0,
		NULL, 0, 60, (ImVec2){size.x / 2, size.y / 3}, 4);
	igText("Render time : %.3fms", (float)sdl->render_time[P_TIME_LEN - 1]);
	igSameLine(size.x / 2, plot_border);
	igText("Gui FPS (%i)", (int)sdl->gui_time[GUI_FPS - 1]);
	igProgressBar(sdl->progress_sub_sample, (ImVec2){size.x / 4, 0},
		"Render progress");
	igText("Path : [%s]\targ : [%s]", app->option.path, app->arg);
	igText("Time animation render : [%.3fs]",
		(float)(app->gui.frames_render_time / 1000.0f));
	igText("Count obj: [%d]\tCount light: [%d]", ft_lstlen(app->scene.lst_obj),
		app->scene.nb_light);
}

void	stats_win(t_gui *gui)
{
	ImVec2 pos;
	ImVec2 size;

	if (gui->demo_open)
		igShowDemoWindow(NULL);
	pos.x = 0;
	pos.y = gui->sdl->height_vp * RENDER_SCALE + MENUBAR_HEIGHT;
	size.x = gui->sdl->width_vp / 2.5;
	size.y = gui->sdl->height_vp - pos.y + 1;
	igSetNextWindowPos(pos, (ImGuiCond_Always), (ImVec2){0, 0});
	igSetNextWindowSizeConstraints(size, size, NULL, NULL);
	igBegin("Stats", &gui->stats_open, ImGuiWindowFlags_NoResize);
	stats_win_content(gui->sdl, size, gui->app);
	igEnd();
}
