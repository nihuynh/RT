/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 13:27:53 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "config.h"
#if defined(__APPLE__)
# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

void	ui_render(t_ui_func *ui)
{
	ui->render_win(ui);
	ui->scene_win(ui);
	if (ui->err_win != NULL)
		ui->err_win(ui);
	if (ui->load_win != NULL)
		ui->load_win(ui);
	if (ui->export_win != NULL)
		ui->export_win(ui);
	if (ui->add_obj_win != NULL)
		ui->add_obj_win(ui);
	if (ui->del_obj_win != NULL)
		ui->del_obj_win(ui);
	if (ui->stats_win != NULL)
		ui->stats_win(ui);
}

void	interface(t_data *app)
{
	ImGuiIO *io;

	io = igGetIO();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(app->sdl.win);
	igNewFrame();
	ui_render(&app->gui.ui);
	if (SHOW_DEMO)
		igShowDemoWindow(NULL);
	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0.107f, 0.277f, 0.348f, 1.000f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(app->sdl.win);
}
