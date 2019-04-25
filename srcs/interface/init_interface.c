/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:08:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/24 14:11:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

void	init_interface(t_gui *gui, SDL_Window *window, t_data *app)
{
	SDL_GLContext gl_context;

	gui->log_open = false;
	gl_context = SDL_GL_CreateContext(window);
	igCreateContext(NULL);
	ImGui_ImplSDL2_InitForOpenGL(window, &gl_context);
	ImGui_ImplOpenGL2_Init();
	glGenTextures(1, &gui->texture_id);
	glBindTexture(GL_TEXTURE_2D, gui->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	gui->light_set = app->lst_light;
	gui->obj_set = NULL;
}
