/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/13 15:02:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#if defined(__APPLE__)
# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

void	window_renderer(t_gui *gui, t_img img)
{
	ImVec2	pos;

	igSetNextWindowPos((ImVec2){0, 0}, gui->flags_render, (ImVec2){0, 0});
	igSetNextWindowSize((ImVec2){img.width, img.height}, 0);
	igPushStyleVarVec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0);
	igBegin("render", NULL, RENDER_FLAGS);
	igImage((void*)(intptr_t)gui->texture_id, (ImVec2){img.width, img.height},
								(ImVec2){0, 0}, (ImVec2){1, 1},
								(ImVec4){1, 1, 1, 1}, (ImVec4){0, 0, 0, 0});
	pos = igGetWindowPos();
	gui->pos_render.x = pos.x;
	gui->pos_render.y = pos.y;
	gui->render_focused = !igIsWindowFocused(0);
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
	window_renderer(gui, img);
	window_scene(app);
	if (gui->log_open)
		window_log(&gui->log_open);
	if (gui->export_open)
		export_window(app);
	if (gui->new_obj_open)
		new_obj_window(app);
	if (gui->delete_obj_open)
		delete_obj_window(app);
	if (gui->load_open)
		load_window(app);
	if (gui->error_open)
		error_window(app);
}

void	update_texture(t_img img, t_gui gui)
{
	glBindTexture(GL_TEXTURE_2D, gui.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_BGRA,
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
	glClearColor(0.107f, 0.277f, 0.348f, 1.000f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(app->sdl.win);
}
