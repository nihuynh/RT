/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 03:33:18 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/25 23:09:14 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libui.h"
#include "t_data.h"
#include "t_gui.h"
#include "interface.h"
#include "SDL_opengl.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

static inline void
	hook_render_to_gui(t_gui *gui, SDL_Window *window)
{
	if (!(gui->gl_context = SDL_GL_CreateContext(window)))
		ft_error(__func__, __LINE__);
	igCreateContext(NULL);
	ImGui_ImplSDL2_InitForOpenGL(window, &gui->gl_context);
	ImGui_ImplOpenGL2_Init();
	glGenTextures(1, &gui->texture_id);
	glBindTexture(GL_TEXTURE_2D, gui->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
	hook_sdl(t_data *app)
{
	app->sdl->key_map = &key_event;
	app->sdl->mouse_map = &mouse_motion;
	app->sdl->update = &update;
	app->sdl->render_gui = &render_gui;
	app->sdl->click_map = &click_event;
	app->sdl->sub_s = 1;
	app->gui.app = app;
	app->gui.sdl = app->sdl;
	hook_render_to_gui(&app->gui, app->sdl->win);
}
