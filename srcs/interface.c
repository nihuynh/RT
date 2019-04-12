/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/12 15:42:06 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "rt.h"
#include <SDL_video.h>
#include <SDL.h>
#include <OpenGL/gl.h>
#include "cimgui.h"
#define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
#define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize
#define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
#define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "libft.h"
typedef struct SDL_Window SDL_Window;

void	window_renderer(t_gui gui, t_img img)
{
	igSetNextWindowSize((ImVec2){img.width, img.height}, 0);
	igPushStyleVarVec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0);
	if(!igBegin("render", NULL, RENDER_FLAGS))
	{
		igEnd();
		return ;
	}
	igImage((void*)(intptr_t)gui.texture_id, (ImVec2){img.width, img.height},
								(ImVec2){0, 0}, (ImVec2){1,1},
								(ImVec4){1, 1, 1, 1}, (ImVec4){0, 0, 0, 0});
	igEnd();
	igPopStyleVar(2);
}

void	window_object()
{
	bool p_bool = true;
	if(!igBegin("Scene", &p_bool, 0))
	{
		igEnd();
		return ;
	}
	igText("Scene modifier here");
	igEnd();
}

void	gui_setup(t_gui gui, t_img img)
{
	window_renderer(gui, img);
	window_object();
}

void	update_texture(t_img img, t_gui gui)
{
	glBindTexture(GL_TEXTURE_2D, gui.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	init_interface(t_gui *gui, SDL_Window *window)
{
	SDL_GLContext gl_context;

	gl_context = SDL_GL_CreateContext(window);
	igCreateContext(NULL);
	ImGui_ImplSDL2_InitForOpenGL(window, &gl_context);
	ImGui_ImplOpenGL2_Init();
	glGenTextures(1, &gui->texture_id);
	glBindTexture(GL_TEXTURE_2D, gui->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	interface(t_gui gui, SDL_Window *window, t_img img)
{
	ImGuiIO *io;

	io = igGetIO();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	igNewFrame();
	gui_setup(gui, img);
	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0.4, 0.55, 0.6, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(window);
}
