/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/24 18:34:26 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ftio.h"
#include "ftstring.h"
#include "interface.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "SDL_opengl.h"

void
	ui_render(t_gui *gui)
{
	render_win(gui);
	ui_mainmenu(gui);
	if (gui->edit_open)
		ui_scene_editor(gui);
	if (gui->render_set_open)
		ui_render_settings(gui->app);
	if (gui->err_open)
		err_win(gui);
	if (gui->stats_open)
		stats_win(gui);
	if (gui->load_open)
		load_win(gui);
	if (gui->export_open)
		export_win(gui);
	if (gui->del_obj_open)
		del_obj_win(gui);
	if (gui->del_light_open)
		del_light_win(gui);
	if (gui->keymap_open)
		keymap_win(gui);
	if (gui->about_open)
		about_win(gui);
}

void
	interface(t_data *app)
{
	ImGuiIO *io;

	io = igGetIO();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(app->sdl->win);
	igNewFrame();
	ui_render(&app->gui);
	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0.107f, 0.277f, 0.348f, 1.000f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(app->sdl->win);
	if (app->gui.animate)
		animate(app);
}

void
	exit_ui(t_gui *gui)
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	if (gui->gl_context)
	{
		igDestroyContext(NULL);
		SDL_GL_DeleteContext(gui->gl_context);
	}
	if (gui->keymap.name)
	{
		ft_strdel(&gui->keymap.name);
		ft_strdel(&gui->keymap.dir);
		ft_memdel((void**)&gui->keymap.pixels);
	}
}

void
	load_nbind_texture(t_texture *tex, uint32_t *bind)
{
	load_texture(tex);
	if (tex->pixels == NULL)
		ft_error(__func__, __LINE__);
	glGenTextures(1, bind);
	glBindTexture(GL_TEXTURE_2D, *bind);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		tex->width, tex->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}
