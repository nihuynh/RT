/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/01 19:13:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include <SDL_video.h>
#include <SDL.h>
#include <OpenGL/gl.h>
#include "cimgui.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

typedef struct SDL_Window SDL_Window;

void	interface(SDL_Window *window)
{
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);

	igCreateContext(NULL);
	ImGui_ImplSDL2_InitForOpenGL(window, &gl_context);
	ImGui_ImplOpenGL2_Init();
	ImGuiIO *io = igGetIO();

	bool done = false;
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
		}

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		igNewFrame();

		igShowDemoWindow(NULL);

		igRender();
		glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
		glClearColor(0.4, 0.55, 0.6, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData());
		SDL_GL_SwapWindow(window);
	}
	exit(0);
}
