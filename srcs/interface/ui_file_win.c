/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_file_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:30:19 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 09:45:34 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "rt.h"

void	err_win(t_ui_func *ui)
{
	igBegin("Error", &ui->err_open, ImGuiWindowFlags_AlwaysAutoResize);
	igText(ui->err_msg);
	if (igButton("Close", (ImVec2){0, 0}))
		ui->err_open = false;
	igEnd();
}

void	export_win(t_ui_func *ui)
{
	char buff[50];

	ft_strcpy(buff, "scenes/");
	ft_strlcat(buff, ui->app->gui.scene_name, 50 - ft_strlen(buff));
	igBegin("Export Scene", &ui->export_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, 50, ImGuiInputTextFlags_EnterReturnsTrue,
			NULL, NULL))
	{
		export_scene(ui->app, buff);
		ui->export_open = false;
	}
	igEnd();
}

void	load_win(t_ui_func *ui)
{
	char		buff[50];

	ft_strlcpy(buff, ui->app->arg, sizeof(buff));
	igBegin("Load Scene", &ui->load_open,
				ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, sizeof(buff),
		ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
	{
		if (check_file(buff))
			load_scene(ui->app, buff);
		else
		{
			ft_strlcpy(ui->err_msg, "File does not exist", sizeof(ui->err_msg));
			ui->err_open = true;
		}
		ui->load_open = false;
	}
	igEnd();
}

void	stats_win(t_ui_func *ui)
{
	igSetNextWindowPos((ImVec2){0, ui->app->sdl->img.height + 18},
		(ImGuiCond_Once), (ImVec2){0, 0});
	igBegin("Stats", &ui->stats_open, ImGuiWindowFlags_AlwaysAutoResize);
	igProgressBar(ui->app->sdl->progress_sub_sample, (ImVec2){150, 0}, "Render");
	igSameLine(220, 0);
	igText("Render time : %fms", ui->app->sdl->render_time[P_TIME_LEN - 1]);
	igText("Gui FPS (%i)", (int)ui->app->sdl->gui_time[GUI_FPS - 1]);
	igPlotLines("Render Time (ms)", &(ui->app->sdl->render_time[0]),
		P_TIME_LEN, 0, NULL, 0, 3.402823466e+38F, (ImVec2){400, 80}, 4);
	igPlotHistogramFloatPtr("Gui FPS", &(ui->app->sdl->gui_time[0]),
		GUI_FPS, 0, NULL, 0, 60, (ImVec2){400, 80}, 4);
	igEnd();
}
