/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/27 12:55:21 by sklepper         ###   ########.fr       */
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

void	window_renderer(t_gui *gui, t_img img)
{
	render_win(gui);
	interface_mainmenu(gui);
	if (gui->edit_open)
		scene_win(gui);
	if (gui->err_open)
		err_win(gui);
	if (gui->stats_open)
		stats_win(gui);
	if (gui->tree_open)
		tree_obj_win(gui);
	if (gui->load_open)
		load_win(gui);
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
	if (SHOW_DEMO)
		igShowDemoWindow(NULL);
	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0.107f, 0.277f, 0.348f, 1.000f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(app->sdl.win);
}
