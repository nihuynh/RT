/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/14 03:58:37 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include <OpenGL/gl.h>
#include "cimgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

void	window_renderer(t_gui gui, t_img img)
{
	igSetNextWindowSize((ImVec2){img.width, img.height}, 0);
	if (RENDER_STATIC)
		igSetNextWindowPos((ImVec2){0, 0}, 0, (ImVec2){0, 0});
	igPushStyleVarVec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0);
	igBegin("render", NULL, RENDER_FLAGS);
	igImage((void*)(intptr_t)gui.texture_id, (ImVec2){img.width, img.height},
								(ImVec2){0, 0}, (ImVec2){1, 1},
								(ImVec4){1, 1, 1, 1}, (ImVec4){0, 0, 0, 0});
	igEnd();
	igPopStyleVar(2);
}

void	window_log(bool *p_open)
{
	igBegin("Log", p_open, 0);
	igText("Logs here");
	igEnd();
}

void	gui_setup(t_gui *gui, t_img img, t_data *app)
{
	window_renderer(*gui, img);
	window_scene(app);
	if (gui->log_open)
		window_log(&gui->log_open);
}

void	update_texture(t_img img, t_gui gui)
{
	glBindTexture(GL_TEXTURE_2D, gui.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, img.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	interface(t_data *app)
{
	ImGuiIO *io;

	io = igGetIO();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(app->sdl.win);
	igNewFrame();
	gui_setup(&app->gui, app->sdl.img, app);
	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0.4, 0.55, 0.6, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(app->sdl.win);
}
